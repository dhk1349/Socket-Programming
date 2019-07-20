#include "packet_structure.h"
#include <iostream>

struct Ethernet_Header{
    unsigned char D_addr[6]; //destination mac address
    unsigned char S_addr[6]; //source mac address
    unsigned short type;     //next layer's type
};

struct IP_Header{
   unsigned char H_length;    //need to be revised to 4bit when value being initialized
   unsigned short T_Length; //
   unsigned short H_checksum; //
   unsigned char S_IP[4];
   unsigned char D_IP[4];
};

struct ARP_Header{
    unsigned short H_type;
    unsigned short P_type;
    unsigned char H_A_length;
    unsigned char P_A_length;
    unsigned short OPcode;
    unsigned char S_H_addr[6];  //source mac
    unsigned int S_P_addr;      //source IP
    unsigned char D_H_addr[6];  //dest mac
    unsigned int D_P_addr;      //dest IP
};

int alloc_eth(unsigned char* h, Ethernet_Header* Eh){
    for(int i=0;i<6;i++){
        Eh->D_addr[i]=h[i];
        Eh->S_addr[i]=h[i+6];
    }
    Eh->type=(h[12]&0x0f);
    return 1;
}

int alloc_IP(unsigned char* h, IP_Header* Ih){
    Ih->H_length=(h[14+1]&0x0f); //1 byte
    Ih->T_Length=(h[14+2]<<16)+h[14+3];
    for(int i=0;i<3;i++){
        Ih->D_IP[i]=h[14+12+i];
        Ih->S_IP[i]=h[14+12+i];
    }
    return 1;
}

int alloc_ARP(unsigned char* h, ARP_Header* Ah){

    return 1;
}
