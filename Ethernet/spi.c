/*
 * spi.c
 *
 * Created: 12/22/2011 9:44:15 AM
 *  Author: Administrator
 */ 

#include "spi.h"

void spi_init()
{
	// Initial the AVR ATMega328 SPI Peripheral
	// Set MOSI (PORTB3),SCK (PORTB5) and PORTB2 (SS) as output, others as input
	SPI_DDR = (1<<PORTB3)|(1<<PORTB5)|(1<<PORTB2);
	// CS pin is not active
	SPI_PORT |= (1<<SPI_CS);
	// Enable SPI, Master Mode 0, set the clock rate fck/2
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR |= (1<<SPI2X);  	
}

void spi_write(uint8_t data)
{
  // Activate the CS pin
  SPI_PORT &= ~(1<<SPI_CS);
  // Set SPDR to data
  SPDR = data;
  // Wait for transmission complete
  while(!(SPSR & (1<<SPIF)));
  // CS pin is not active
  SPI_PORT |= (1<<SPI_CS);
}

uint8_t spi_read(void)
{
	uint8_t data;
	// Activate the CS pin
	SPI_PORT &= ~(1<<SPI_CS);
	// Set temp value for SPDR
	SPDR = 0x00;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	// CS pin is not active
	SPI_PORT |= (1<<SPI_CS);
	return(data);
}