#pragma once
#include "libraries.h"


typedef struct Ethernet_Header{
    unsigned char D_addr[6]; //destination mac address
    unsigned char S_addr[6]; //source mac address
    unsigned short type;     //next layer's type
}Ethernet_Header;

typedef struct IP_Header{
   unsigned char H_length;    //need to be revised to 4bit when value being initialized
   unsigned short T_Length; //
   unsigned short H_checksum; //
   unsigned char S_IP[4];
   unsigned char D_IP[4];
}IP_Header;

typedef struct ARP_Header{
    unsigned short H_type;
    unsigned short P_type;
    unsigned char H_A_length;
    unsigned char P_A_length;
    unsigned short OPcode;
    unsigned char S_H_addr[6];  //source mac
    unsigned char S_P_addr[4];      //source IP
    unsigned char D_H_addr[6];  //dest mac
    unsigned char D_P_addr[4];      //dest IP
}ARP_Header;

void default_setting(Ethernet_Header *eth, ARP_Header* arp);
void set_eth_mac(Ethernet_Header* eth, uint8_t* Source_mac, uint8_t* Dest_mac);
void set_arp_mac(ARP_Header* arp, uint8_t* Sender_mac, uint8_t* Dest_mac);
void set_arp_IP(ARP_Header* arp, uint8_t* Sender_IP, uint8_t* Dest_IP);
void set_arp_OP(ARP_Header* arp, int input);
void Broadcast_Setting(Ethernet_Header* eth, ARP_Header* arp,uint8_t* S_MAC, uint8_t* S_IP, uint8_t* D_IP);
void Infection_Setting(Ethernet_Header *eth, ARP_Header* arp, uint8_t* attacker_MAC, uint8_t* victim_MAC, uint8_t* victim_IP, uint8_t* Real_IP);

void GET_MY_IP_MAC(char* dev, uint8_t* attacker_IP, uint8_t* attacker_MAC);
