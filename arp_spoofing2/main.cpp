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

    uint8_t* targte_IP;
    uint8_t* target_MAC;

    //detect my mac
    GET_MY_IP_MAC(dev, attacker_IP, attacker_MAC);

    //detect sender mac
    attack_info.Broadcast_Setting(attacker_MAC, attacker_IP, sender_IP);


    //infect sender mac table.
    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
