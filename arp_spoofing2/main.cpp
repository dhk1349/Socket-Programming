#include <iostream>
#include <pcap.h>
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
     printf("start\n");
    if(argc!=4){
        usage();
        exit(1);
    }
    printf("Before calling constructor\n");
    Header attack_info;
    printf("after calling constructor\n");
    char* dev=argv[1];
    uint8_t attacker_IP[4];
    uint8_t attacker_MAC[6];

    uint8_t sender_IP[4];
    uint8_t sender_MAC[6];

    uint8_t target_IP[4];
    uint8_t target_MAC[6];
    printf("2\n");

    printf("before calling memecopy\n");
    const char* sender_ip_str=argv[2];
    const char* target_ip_str=argv[3];
    inet_pton(AF_INET, sender_ip_str, sender_IP);
    inet_pton(AF_INET, target_ip_str, target_IP);
    //detect my mac
    printf("Before calling getmy ip mac\n");
    GET_MY_IP_MAC(dev, attacker_IP, attacker_MAC);
    printf("3\n");

    //Initialize handler
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;//for pcap_next_ex
    pcap_t *handle=pcap_open_live(dev,BUFSIZ, 1, 1000, errbuf );
    if(handle==NULL){
        printf("FAILED TO OPEN PCAP HANDLE\n");
        return -1;
    }
    printf("4\n");

    //detect sender mac
    attack_info.Broadcast_Setting(attacker_MAC, attacker_IP, sender_IP);
    printf("setting for BC done\n");
    while(1){
        printf("while \n\n");
        char* sendpacket;
        attack_info.get_packet(sendpacket);
        const u_char* packet;
        pcap_sendpacket(handle,(u_char *) sendpacket, 42);

        int response=pcap_next_ex(handle, &header, &packet);
        if(response==0) continue;
        printf("running\n");
    }
    //detecting target mac
    printf("broadcasting of info\n\n");
    attack_info.Broadcast_Setting(attacker_MAC, attacker_IP, target_IP);

    //infect sender mac table.


    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
