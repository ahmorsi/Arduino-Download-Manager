/*
 * socket_Utilities.h
 *
 * Created: 22/12/2012 06:59:31 م
 *  Author: Ahmed Emad Morsy
 */ 

#include <stdint.h>

#ifndef SOCKET_UTILITIES_H_
#define SOCKET_UTILITIES_H_

uint8_t get_socket0_status(void);
uint8_t get_socket1_status(void);
uint8_t get_socket2_status(void);
uint8_t get_socket3_status(void);

uint16_t S0_TX_getFreeSize(void);
uint16_t S1_TX_getFreeSize(void);
uint16_t S2_TX_getFreeSize(void);
uint16_t S3_TX_getFreeSize(void);

uint16_t S0_TX_getWriteAddress(void);
uint16_t S1_TX_getWriteAddress(void);
uint16_t S2_TX_getWriteAddress(void);
uint16_t S3_TX_getWriteAddress(void);



#endif /* SOCKET_UTILITIES_H_ */