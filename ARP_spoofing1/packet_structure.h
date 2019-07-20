#ifndef __packet_structure__
#define request 0x0001;  //ARP OPcode
#define reply 0x0002;
#define R_request 0x0003;
#define R_reply 0x0004;

struct Ethernet_Header;

struct IP_Header;

struct ARP_Header;

int alloc_eth(unsigned char* h, Ethernet_Header* Eh); //put first addr
int alloc_IP(unsigned char* h, IP_Header* Ih);
int alloc_ARP(unsigned char* h, ARP_Header* Ah);
#endif
