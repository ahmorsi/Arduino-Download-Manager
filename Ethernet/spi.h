/*
 * spi.h
 *
 * Created: 12/22/2011 9:44:07 AM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <stdint.h>

#ifndef SPI_H_
#define SPI_H_

// ATMega328 SPI I/O
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_CS   PORTB2

/*
	Initialize SPI.
*/
void spi_init();

/*
	Writes data to SPI at Address addr.
*/
void spi_write(uint8_t data);

/*
	Reads byte from SPI.
*/
unsigned char spi_read();

#endif /* SPI_H_ */