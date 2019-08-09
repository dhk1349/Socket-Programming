#include "protocol_class.h"


Header::Header(){
    packet=(char*)malloc(sizeof(char)*42);
    Ethernet *eth=(Ethernet *)packet;
    ARP * arp=(ARP *)packet;

    eth->type=htons(0x0806); //Next layer will be ARP
    arp->H_type=htons(0x0001);
    arp->P_type=htons(0x0800);
    arp->H_A_length=0x06;
    arp->P_A_legnth=0x04;
}

Header::Header(std::string OP){
    Header();
    if(OP=="Request") arp->OPcode=htons(0x0001);
    if(OP=="Reply") arp->OPcode=htons(0x0002);
}
void Header::set_eth_mac(int8_t Source_mac[6], int8_t Dest_mac[6]){
    memcpy(eth->S_addr, Source_mac,  6);
    memcpy(eth->D_addr, Dest_mac, 6);
}
void Header::set_arp_mac(int8_t Sender_mac[6], int8_t Dest_mac[6]){
    memcpy(arp->S_H_addr, Sender_mac, 6);
    memcpy(arp->D_H_addr, Dest_mac, 6);
}
void Header::set_arp_IP(int8_t Sender_IP[4], int8_t Dest_IP[4]){
    memcpy(arp->D_P_addr, Dest_IP, 4);
    memcpy(arp->S_P_addr, Sender_IP, 4);
}
void Header::get_packet(char* input){
    input=packet;
}
