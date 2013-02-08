/*
 * ethernet.c
 *
 * Created: 12/22/2011 9:44:35 AM
 *  Author: Administrator
 */ 

#include <avr/delay.h>
#include "wiznet.h"
#include "spi.h"
#include "ansi.h"
void w5100_init(void)
{
 // Ethernet Setup
  unsigned char mac_addr[] = {0x90,0xA2,0xDA,0x0D,0x2F,0xC7};
  unsigned char ip_addr[] = {10,0,0,6};
  unsigned char sub_mask[] = {255,0,0,0};
  unsigned char gtw_addr[] = {10,0,0,6};
  // Setting the Wiznet W5100 Mode Register: 0x0000
  wiznet_write(MR,0x80);            // MR = 0b10000000;
  _delay_ms(1);
  printf("Reading MR: %d\n\n",wiznet_read(MR));
  // Setting the Wiznet W5100 Gateway Address (GAR): 0x0001 to 0x0004
  printf("Setting Gateway Address %d.%d.%d.%d\n",gtw_addr[0],gtw_addr[1],\
          gtw_addr[2],gtw_addr[3]);
  wiznet_write(GAR + 0,gtw_addr[0]);
  wiznet_write(GAR + 1,gtw_addr[1]);
  wiznet_write(GAR + 2,gtw_addr[2]);
  wiznet_write(GAR + 3,gtw_addr[3]);
  _delay_ms(1);
  printf("Reading GAR: %d.%d.%d.%d\n\n",wiznet_read(GAR + 0),wiznet_read(GAR + 1),\
          wiznet_read(GAR + 2),wiznet_read(GAR + 3));
  // Setting the Wiznet W5100 Source Address Register (SAR): 0x0009 to 0x000E
  printf("Setting Source Address %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",mac_addr[0],mac_addr[1],\
          mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
  wiznet_write(SAR + 0,mac_addr[0]);
  wiznet_write(SAR + 1,mac_addr[1]);
  wiznet_write(SAR + 2,mac_addr[2]);
  wiznet_write(SAR + 3,mac_addr[3]);
  wiznet_write(SAR + 4,mac_addr[4]);
  wiznet_write(SAR + 5,mac_addr[5]);
  _delay_ms(1);
  printf("Reading SAR: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n\n",wiznet_read(SAR + 0),wiznet_read(SAR + 1),\
          wiznet_read(SAR + 2),wiznet_read(SAR + 3),wiznet_read(SAR + 4),wiznet_read(SAR + 5));
  // Setting the Wiznet W5100 Sub Mask Address (SUBR): 0x0005 to 0x0008
  printf("Setting Sub Mask Address %d.%d.%d.%d\n",sub_mask[0],sub_mask[1],\
          sub_mask[2],sub_mask[3]);
  wiznet_write(SUBR + 0,sub_mask[0]);
  wiznet_write(SUBR + 1,sub_mask[1]);
  wiznet_write(SUBR + 2,sub_mask[2]);
  wiznet_write(SUBR + 3,sub_mask[3]);
  _delay_ms(1);
  printf("Reading SUBR: %d.%d.%d.%d\n\n",wiznet_read(SUBR + 0),wiznet_read(SUBR + 1),\
          wiznet_read(SUBR + 2),wiznet_read(SUBR + 3));
  // Setting the Wiznet W5100 IP Address (SIPR): 0x000F to 0x0012
  printf("Setting IP Address %d.%d.%d.%d\n",ip_addr[0],ip_addr[1],\
          ip_addr[2],ip_addr[3]);
  wiznet_write(SIPR + 0,ip_addr[0]);
  wiznet_write(SIPR + 1,ip_addr[1]);
  wiznet_write(SIPR + 2,ip_addr[2]);
  wiznet_write(SIPR + 3,ip_addr[3]);
  _delay_ms(1);
  printf("Reading SIPR: %d.%d.%d.%d\n\n",wiznet_read(SIPR + 0),wiznet_read(SIPR + 1),\
          wiznet_read(SIPR + 2),wiznet_read(SIPR + 3));

  // Setting the Wiznet W5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels
  printf("Setting Wiznet RMSR and TMSR\n\n");
  wiznet_write(RMSR,0x55);
  wiznet_write(TMSR,0x55);
  
  // Setting the Wiznet W5100 timeout with 2000ms
  wiznet_write(RTR,0x9C);
  wiznet_write(RTR + 1,0x40);
  printf("Setting the timeout period of W5100 with %d ms\n",4000);
  
  printf("Done Wiznet W5100 Initialized!\n");
}

/*
	Write command to Ethernet controller.
*/
void wiznet_write(uint16_t addr,uint8_t data)
{
  // Send Wiznet W5100 Write OpCode transmission
  spi_write(WIZNET_WRITE_OPCODE);
  
  // Send Wiznet W5100 Address High Bytes transmission
  spi_write((addr & 0xFF00) >> 8);
  
  // Send Wiznet W5100 Address Low Bytes transmission
  spi_write(addr & 0x00FF);
  
  // Start Data transmission
  spi_write(data);
}

/*
	Read command from Ethernet controller.
*/
unsigned char wiznet_read(uint16_t addr)
{
  // Send Wiznet W5100 Read OpCode transmission
  spi_write(WIZNET_READ_OPCODE);
  
  // Send Wiznet W5100 Address High Bytes transmission
  spi_write((addr & 0xFF00) >> 8);
  
  // Send Wiznet W5100 Address Low Bytes transmission
  spi_write(addr & 0x00FF);
  
  // Read character from SPI
  return spi_read();
}
uint16_t gSn_RX_MASK(uint8_t socketNum)
{
	uint8_t socketSizeState= wiznet_read(RMSR) << ( 6-(2*socketNum));
	socketSizeState = (socketSizeState >> 6) + 10;
	uint16_t socketMaxSize = 1 << socketSizeState;
	return socketMaxSize -1;	
}
uint16_t gSn_TX_MASK(uint8_t socketNum)
{
	uint8_t socketSizeState= wiznet_read(TMSR) << ( 6-(2*socketNum));
	socketSizeState = (socketSizeState >> 6) + 10;
	uint16_t socketMaxSize = 1 << socketSizeState;
	return socketMaxSize -1;
}