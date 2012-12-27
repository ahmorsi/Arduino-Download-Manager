/*
 * uart.h
 *
 * Created: 12/22/2011 9:43:58 AM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <stdio.h>

#ifndef UART_H_
#define UART_H_

/*
	Initialize UART using 9600 BAUD Rate suitable for the
	ATMEGA328P. This function is ready made.
*/
void uart_init(void);

/*
	Flush the buffer to make sure everything is sent.
*/
void uart_flush(void);

/*
	Write a char to the stream.
*/
int uart_putch(char ch,FILE *stream);

/*
	Get a char from the stream.
*/
int uart_getch(FILE *stream);

#endif /* UART_H_ */