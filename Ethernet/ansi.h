/*
 * ansi.h
 *
 * Created: 12/22/2011 10:05:55 AM
 *  Author: Administrator
 */ 

#include <stdio.h>
#include "uart.h"

#ifndef ANSI_H_
#define ANSI_H_

FILE uart_str = FDEV_SETUP_STREAM(uart_putch, uart_getch, _FDEV_SETUP_RW);
/*
	Initialize the Standard Output streams for ANSI
*/
void ansi_init(void);

/*
	ANSI clear screen: cl=\E[H\E[J
*/
void ansi_cl(void);

/*
	ANSI turn off all attribute: me=\E[0m
*/
void ansi_me(void);


#endif /* ANSI_H_ */