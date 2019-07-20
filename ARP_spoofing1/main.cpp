#include<iostream>
#include<pcap.h>
using namespace std;
int usage(){
    cerr<<"Syntax: Send_arp <interface><sender IP><target IP>\n";
    cerr<<"Sample: Send_arp wlan0 192.168.10.2 102.160.10.1\n";
    return -1;
}
//Suppose victim's ip is given.
int main(int argc, char* argv[]){
    if(argc!=4){
        usage();
        return -1;
    }


    //code for catching mac addr

    //Sending arp packet
    return 0;
}
