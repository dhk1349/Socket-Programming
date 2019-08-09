#ifndef PROTOCOL_CLASS_H
#define PROTOCOL_CLASS_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
struct Object{
    uint8_t MAC[6];
    uint8_t IP[4];
};

struct Data{
    Object Attacker;
    Object Sender;
    Object Target;
};

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
    Header();
    Header(std::string OP);
    void set_eth_mac(int8_t Source_mac[6], int8_t Dest_mac[6]);
    void set_arp_mac(int8_t Sender_mac[6], int8_t Dest_mac[6]);
    void set_arp_IP(int8_t Sender_IP[4], int8_t Dest_IP[4]);
    void get_packet(char* input);
};
#endif // PROTOCOL_CLASS_H
