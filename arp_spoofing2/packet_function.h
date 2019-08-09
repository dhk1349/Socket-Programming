#ifndef PACKET_FUNCTION_H
#define PACKET_FUNCTION_H
#include <stdint.h>
#include "protocol_class.h"
void GET_MY_IP_MAC(char * dev, uint8_t * ip_attacker, uint8_t * mac_attacker);

void GET_MAC(Data data);
#endif // PACKET_FUNCTION_H
