#include <iostream>
#include <pcap.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include <net/if.h>
#include<netinet/ether.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include "protocol_class.h"
#include "packet_function.h"
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
    char* dev;
    uint8_t Attacker_MAC[6]; //MY MAC
    uint8_t Attacker_IP[4];  //MY IP
    uint8_t Sender_MAC[6];   //VICTIM's MAC
    uint8_t Sender_IP[4];    //VICTIMS's IP
    uint8_t Target_MAC[6];   //GATEWAY's MAC
    uint8_t Target_IP[4];    //GATEWAY's IP

    dev=argv[0];
    memcpy(Sender_IP,argv[1],4);
    memcpy(Target_IP,argv[2],4);

    //detect my mac
    GET_MY_IP_MAC(dev, Attacker_IP, Attacker_MAC);


    //detect sender mac
    //infect sender mac table.
    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
