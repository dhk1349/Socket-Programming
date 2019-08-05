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
int GET_MY_MAC(char* dev, uint8_t * attacker_IP, uint8_t attacker_mac){
    return 1 ;
}
 int main(int argc, char* argv[])
{
    if(argc!=3){
        usage();
        exit(1);
    }
    //detect my mac
    //detect sender mac
    //infect sender mac table.
    //infect target mac tagble.

    //receive packet from sender
    //send received packet to target

    //receive result packet from target
    //pass result packet to sender

    return 0;
}
