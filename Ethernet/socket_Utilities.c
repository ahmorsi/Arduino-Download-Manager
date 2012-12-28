/*
 * socket_Utilities.c
 *
 * Created: 22/12/2012 07:00:49 م
 *  Author: Ahmed Emad Morsy
 */ 
#include "socket_Utilities.h"
#include "wiznet.h"
uint8_t get_socket0_status(void)
{
	// Here you should referee to the data sheet to see which register should be read.
	// refer back to page 16
	return wiznet_read(S0_SR);
}
uint8_t get_socket1_status(void)
{
	// Here you should referee to the data sheet to see which register should be read.
	// refer back to page 16
	return wiznet_read(S1_SR);
}
uint8_t get_socket2_status(void)
{
	// Here you should referee to the data sheet to see which register should be read.
	// refer back to page 16
	return wiznet_read(S2_SR);
}
uint8_t get_socket3_status(void)
{
	// Here you should referee to the data sheet to see which register should be read.
	// refer back to page 16
	return wiznet_read(S3_SR);
}
uint16_t S0_TX_getFreeSize(void)
{
	uint8_t socket0_TX_FSR [2];
	socket0_TX_FSR[0]=wiznet_read(S0_TX_FSR);
	socket0_TX_FSR[1]=wiznet_read(S0_TX_FSR + 1);
	return *(uint16_t*)socket0_TX_FSR;
}
uint16_t S1_TX_getFreeSize(void)
{
	uint8_t socket1_TX_FSR [2];
	socket1_TX_FSR[0]=wiznet_read(S1_TX_FSR);
	socket1_TX_FSR[1]=wiznet_read(S1_TX_FSR + 1);
	return *(uint16_t*)socket1_TX_FSR;
}
uint16_t S2_TX_getFreeSize(void)
{
	uint8_t socket2_TX_FSR [2];
	socket2_TX_FSR[0]=wiznet_read(S2_TX_FSR);
	socket2_TX_FSR[1]=wiznet_read(S2_TX_FSR + 1);
	return *(uint16_t*)socket2_TX_FSR;
}
uint16_t S3_TX_getFreeSize(void)
{
	uint8_t socket3_TX_FSR [2];
	socket3_TX_FSR[0]=wiznet_read(S3_TX_FSR);
	socket3_TX_FSR[1]=wiznet_read(S3_TX_FSR + 1);
	return *(uint16_t*)socket3_TX_FSR;
}

uint16_t S0_TX_getWriteAddress(void)
{
	uint8_t socket0_TX_WR[2];
	socket0_TX_WR[0]=wiznet_read(S0_TX_WR);
	socket0_TX_WR[1]=wiznet_read(S0_TX_WR + 1);
	return *(uint16_t*)socket0_TX_WR;
}
uint16_t S1_TX_getWriteAddress(void)
{
	uint8_t socket1_TX_WR[2];
	socket1_TX_WR[0]=wiznet_read(S1_TX_WR);
	socket1_TX_WR[1]=wiznet_read(S1_TX_WR + 1);
	return *(uint16_t*)socket1_TX_WR;
}
uint16_t S2_TX_getWriteAddress(void)
{
	uint8_t socket2_TX_WR[2];
	socket2_TX_WR[0]=wiznet_read(S2_TX_WR);
	socket2_TX_WR[1]=wiznet_read(S2_TX_WR + 1);
	return *(uint16_t*)socket2_TX_WR;
}
uint16_t S3_TX_getWriteAddress(void)
{
	uint8_t socket3_TX_WR[2];
	socket3_TX_WR[0]=wiznet_read(S3_TX_WR);
	socket3_TX_WR[1]=wiznet_read(S3_TX_WR + 1);
	return *(uint16_t*)socket3_TX_WR;
}
uint16_t S0_RX_getReadAddress(void)
{
	uint8_t socket0_RX_RD[2];
	socket0_RX_RD[0]=wiznet_read(S0_RX_RD);
	socket0_RX_RD[1]=wiznet_read(S0_RX_RD + 1);
	return *(uint16_t*)socket0_RX_RD;
}
uint16_t S1_RX_getReadAddress(void)
{
	uint8_t socket1_RX_RD[2];
	socket1_RX_RD[0]=wiznet_read(S1_RX_RD);
	socket1_RX_RD[1]=wiznet_read(S1_RX_RD + 1);
	return *(uint16_t*)socket1_RX_RD;
}
uint16_t S2_RX_getReadAddress(void)
{
	uint8_t socket2_RX_RD[2];
	socket2_RX_RD[0]=wiznet_read(S2_RX_RD);
	socket2_RX_RD[1]=wiznet_read(S2_RX_RD + 1);
	return *(uint16_t*)socket2_RX_RD;
}
uint16_t S3_RX_getReadAddress(void)
{
	uint8_t socket3_RX_RD[2];
	socket3_RX_RD[0]=wiznet_read(S3_RX_RD);
	socket3_RX_RD[1]=wiznet_read(S3_RX_RD + 1);
	return *(uint16_t*)socket3_RX_RD;
}
uint16_t S0_RX_getReceivedSize(void)
{
	uint8_t socket0_RX_RSR[2];
	socket0_RX_RSR[0]=wiznet_read(S0_RX_RSR);
	socket0_RX_RSR[1]=wiznet_read(S0_RX_RSR + 1);
	return *(uint16_t*)socket0_RX_RSR;
}
uint16_t S1_RX_getReceivedSize(void)
{
	uint8_t socket1_RX_RSR[2];
	socket1_RX_RSR[0]=wiznet_read(S1_RX_RSR);
	socket1_RX_RSR[1]=wiznet_read(S1_RX_RSR + 1);
	return *(uint16_t*)socket1_RX_RSR;
}
uint16_t S2_RX_getReceivedSize(void)
{
	uint8_t socket2_RX_RSR[2];
	socket2_RX_RSR[0]=wiznet_read(S2_RX_RSR);
	socket2_RX_RSR[1]=wiznet_read(S2_RX_RSR + 1);
	return *(uint16_t*)socket2_RX_RSR;
}
uint16_t S3_RX_getReceivedSize(void)
{
	uint8_t socket3_RX_RSR[2];
	socket3_RX_RSR[0]=wiznet_read(S3_RX_RSR);
	socket3_RX_RSR[1]=wiznet_read(S3_RX_RSR + 1);
	return *(uint16_t*)socket3_RX_RSR;
}