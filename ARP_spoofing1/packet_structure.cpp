#include "packet_structure.h"
#include <iostream>

int alloc_eth(unsigned char*desmac, unsigned char*mymac, unsigned short nexttype, Ethernet_Header* Eh){
    for(int i=0;i<6;i++){
        Eh->D_addr[i]=desmac[i];
        Eh->S_addr[i]=mymac[i];
    }
    Eh->type=nexttype;
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

int alloc_ARP(unsigned short H_t, unsigned short P_t, unsigned char H_A_l, unsigned char P_A_l,
              unsigned short OP, unsigned char S_H_a[6], unsigned char S_P_a[4],unsigned char D_H_a[6], unsigned char D_P_a[4], ARP_Header* Ah){
    Ah->H_type=H_t;
    Ah->P_type=P_t;
    Ah->H_A_length=H_A_l;
    Ah->P_A_length=P_A_l;
    Ah->OPcode=OP;
    for(int i=0;i<4;i++){
        Ah->S_P_addr[i]=S_P_a[i];
        Ah->D_P_addr[i]=D_P_a[i];
    }
    for(int i=0;i<6;i++){
        Ah->S_H_addr[i]=S_H_a[i];
        Ah->D_H_addr[i]=D_H_a[i];
    }
    return 1;
}
