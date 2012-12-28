/*
 * ethernet.h
 *
 * Created: 12/22/2011 11:50:27 AM
 *  Author: Administrator
 */ 

#include "wiznet.h"

#ifndef ETHERNET_H_
#define ETHERNET_H_

#define MAX_BUF 512
#define TRUE 1
#define FALSE 0
uint8_t buf[MAX_BUF];


uint8_t S0_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port);
uint8_t S1_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port);
uint8_t S2_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port);
uint8_t S3_initialize_socket3(uint8_t eth_protocol,uint16_t tcp_port);

void close(int socket_num);
void disconnect(int socket_num);

uint8_t S0_listen(void);
uint8_t S1_listen(void);
uint8_t S2_listen(void);
uint8_t S3_listen(void);

void S0_connect(const uint8_t *ip,const uint8_t *port);
void S1_connect(const uint8_t *ip,const uint8_t *port);
void S2_connect(const uint8_t *ip,const uint8_t *port);
void S3_connect(const uint8_t *ip,const uint8_t *port);

uint16_t S0_send(const uint8_t *buf,uint16_t buflen);
uint16_t S1_send(const uint8_t *buf,uint16_t buflen);
uint16_t S2_send(const uint8_t *buf,uint16_t buflen);
uint16_t S3_send(const uint8_t *buf,uint16_t buflen);

uint16_t S0_recv(uint8_t *buf,uint16_t buflen);
uint16_t S1_recv(uint8_t *buf,uint16_t buflen);
uint16_t S2_recv(uint8_t *buf,uint16_t buflen);
uint16_t S3_recv(uint8_t *buf,uint16_t buflen);

uint16_t recv_size(void);


#endif /* ETHERNET_H_ */