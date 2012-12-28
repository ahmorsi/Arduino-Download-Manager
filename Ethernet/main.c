/*
 * Ethernet.c
 *
 * Created: 12/22/2011 8:52:47 AM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "ethernet.h"


// Debugging Mode, 0 - Debug OFF, 1 - Debug ON
#define _DEBUG_MODE      0

#define BAUD_RATE 19200

// Define W5100 Socket Register and Variables Used
uint8_t sockreg;
int tempvalue;
uint8_t ledmode,ledeye,ledsign;


int strindex(char *s,char *t)
{
	// this method returns the index of s if found in string t
	// otherwise it returns -1
}

int main(void)
{
	// set port d as output with initial value of zeros

	uart_init();// Initialize UART Peripheral
  
	// Clear the Screen of the hyper terminal <send clear code>
  
	spi_init();// Initialize SPI

	w5100_init();// Initial the W5100 Ethernet
  
  // Loop forever
  while(1)
  {
	  // keep reading the socket zero status
	  // and handle at least socket closed and socket established
	  
	uint8_t sockstat=get_socket0_status();
	switch(sockstat/*Handle all possible socket status here*/) 
	{
	case SOCK_CLOSED:
		break;
	case SOCK_ESTABLISHED:
		// Get the client request size
		// And read the client Request in temp buffer
		// make sure the temp buffer is sending GET request
		// create a buffer that will hold the response and send it
		// if the GET request has an option to turn on/off a LED Carry that now.
		// finally disconnect the socket with the client.
		break;
      case SOCK_FIN_WAIT:
      case SOCK_CLOSING:
      case SOCK_TIME_WAIT:
      case SOCK_CLOSE_WAIT:
      case SOCK_LAST_ACK:
		// force the socket to be closed
		break;
	}		
  }
  return 0;
}