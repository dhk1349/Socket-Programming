#include <iostream>
#include "protocol_class.h"
using namespace std;

/*
conditions
-> Use sender and target ONLY.
->
*/

int usage(){
    cerr<<"Wrong Input Type\n";
    cerr<<"Syntax: ARP_spoof <interface> <Sender IP> <Target IP>";
    return 1;
}
 int main(int argc, char* argv[])
{
    if(argc!=3){
        usage();
        exit(1);
    }

    Header attack_info;
    char* dev=argv[0];
    uint8_t* attacker_IP;
    uint8_t* attacker_MAC;

    uint8_t* sender_IP;
    uint8_t* sender_MAC;

    uint8_t* target_IP;
    uint8_t* target_MAC;

    memcpy(sender_IP, argv[1], 4);
    memcpy(target_IP, argv[2], 4);
    //detect my mac
    GET_MY_IP_MAC(dev, attacker_IP, attacker_MAC);

    //Initialize handler
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;//for pcap_next_ex
    pcap_t *handle=pcap_open_live(dev,BUFSIZ, 1, 1000, errbuf );
    if(handle==NULL){
        printf("FAILED TO OPEN PCAP HANDLE\n");
        return -1;
    }

    //detect sender mac
    attack_info.Broadcast_Setting(attacker_MAC, attacker_IP, sender_IP);
    while(1){
        char* sendpacket;
        attack_info.get_packet(sendpacket);
        const u_char* packet;
        pcap_sendpacket(handle,(u_char *) sendpacket, 42);

        int response=pcap_next_ex(handle, &header, &packet);
        if(response==00) continue;
        printf("running\n");
    }
    //detecting target mac
    attack_info.Broadcast_Setting(attacker_MAC, attacker_IP, target_IP);

    //infect sender mac table.


    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
