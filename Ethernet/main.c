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
#include "ansi.h"
uint8_t dest_ip[]={173,194,32,95};
uint8_t dest_port[]={0,80};
char url[]="www.acmascis.com/index.php";
char httpV[]="HTTP/1.1";
char method[]="GET";	
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
	ansi_init();
	uart_init();// Initialize UART Peripheral
  
	// Clear the Screen of the hyper terminal <send clear code>
  
	spi_init();// Initialize SPI

	w5100_init();// Initial the W5100 Ethernet
  
	if(S0_initialize_socket(MR_TCP,30000))
	{
		printf("INIT DONE 2\n");
		S0_connect(dest_ip,dest_port);
	}	
	
	printf("%x\n",get_socket0_status());
	uart_putch('\0',&uart_str);
	uart_flush();
	
	char* host = http_extract_host(url);
	char* relativeAddress = http_extract_relativeAddress(url,strlen(host));
	char* request = http_create_request(method,relativeAddress,httpV,host);
	printf("%s",request);
	S0_connect(dest_ip,dest_port);
	
	if(get_socket0_status() == SOCK_ESTABLISHED)
	{
		printf("Connected\n");
		uart_putch('\0',&uart_str);
	}
	printf("HTTP\n");
	uart_putch('\0',&uart_str);
	uart_flush();
	
  // Loop forever
  while(1)
  {
	  // keep reading the socket zero status
	  // and handle at least socket closed and socket established
	  
	uint8_t sockstat=get_socket0_status();

	switch(sockstat/*Handle all possible socket status here*/) 
	{
	case SOCK_CLOSED:
		//printf("ERROR1\n");
		//uart_putch('\0',&uart_str);
		//S0_connect(dest_ip,dest_port);
		printf("%x\n",get_socket0_status());
		uart_putch('\0',&uart_str);
		break;
	case SOCK_ESTABLISHED:
		printf("SOCK_ESTABLISHED\n");
		uart_putch('\0',&uart_str);
		// Get the client request size
		// And read the client Request in temp buffer
		// make sure the temp buffer is sending GET request
		S0_send((uint8_t*)request,strlen(request));
		printf("Request Sent\n");
		uart_flush();
		_delay_ms(2000);
		if(S0_RX_getReceivedSize() != 0)
		{
			printf("RECV Response\n");
			uart_putch('\0',&uart_str);
		}
		// create a buffer that will hold the response and send it
		// if the GET request has an option to turn on/off a LED Carry that now.
		// finally disconnect the socket with the client.
		break;
      case SOCK_FIN_WAIT:
      case SOCK_CLOSING:
		printf("closing\n");
		break;
      case SOCK_TIME_WAIT:
      case SOCK_CLOSE_WAIT:
      case SOCK_LAST_ACK:
		printf("ERROR2\n\0");
		uart_putch('\0',&uart_str);
		// force the socket to be closed
		break;
	default:
		printf("nothing");	
	}		
  }
  return 0;
}