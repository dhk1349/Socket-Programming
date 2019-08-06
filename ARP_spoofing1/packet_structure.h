#ifndef __packet_structure__


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

int alloc_eth(unsigned char*desmac, unsigned char*mymac, unsigned short nexttype, Ethernet_Header* Eh); //put first addr
int alloc_IP(unsigned char* h, IP_Header* Ih);
int alloc_ARP(unsigned short H_t, unsigned short P_t, unsigned char H_A_l, unsigned char P_A_l,
              unsigned short OP, unsigned char S_H_a[6], unsigned char S_P_a[3],unsigned char D_H_a[6], unsigned char D_P_a[3], ARP_Header* Ah);

#endif
