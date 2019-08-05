#ifndef PROTOCOL_CLASS_H
#define PROTOCOL_CLASS_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>

struct  Ethernet{
    unsigned char D_addr[6];//destination mac addr
    unsigned char S_addr[6];//source mac addr
    unsigned short type;  //next layer's type 2bytes
};
struct ARP{
    unsigned short H_type;
    unsigned short P_type;
    unsigned char H_A_length;
    unsigned char P_A_legnth;
    unsigned short OPcode;
    unsigned char S_H_addr[6];//source mac
    unsigned char S_P_addr[4];//source IP
    unsigned char D_H_addr[6];//dest mac
    unsigned char D_P_addr[4];//dest IP
};

class Header{
private:
    char* packet;
    Ethernet* eth;
    ARP* arp;
public:
    Header(){
        packet=(char*)malloc(sizeof(char)*42);
        Ethernet *eth=(Ethernet *)packet;
        ARP * arp=(ARP *)packet;

        eth->type=htons(0x0806); //Next layer will be ARP
        arp->H_type=htons(0x0001);
        arp->P_type=htons(0x0800);
        arp->H_A_length=0x06;
        arp->P_A_legnth=0x04;
    }
    Header(std::string OP){
        Header();
        if(OP=="Request") arp->OPcode=htons(0x0001);
        if(OP=="Reply") arp->OPcode=htons(0x0002);
    }
    void set_eth_mac(int8_t Source_mac[6], int8_t Dest_mac[6]){
        memcpy(eth->S_addr, Source_mac,  6);
        memcpy(eth->D_addr, Dest_mac, 6);
    }
    void set_arp_mac(int8_t Sender_mac[6], int8_t Dest_mac[6]){
        memcpy(arp->S_H_addr, Sender_mac, 6);
        memcpy(arp->D_H_addr, Dest_mac, 6);
    }
    void set_arp_IP(int8_t Sender_IP[4], int8_t Dest_IP[4]){
        memcpy(arp->D_P_addr, Dest_IP, 4);
        memcpy(arp->S_P_addr, Sender_IP, 4);
    }
    void get_packet(char* input){
        input=packet;
    }
};
#endif // PROTOCOL_CLASS_H
