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
uint8_t dest_ip[]={10,0,0,5};
uint8_t dest_port[]={0x1F,0x92};
char url[]="10.0.0.5:8082/test.html";
char httpV[]="HTTP/1.1";
char method[]="GET";
char* host,*relativeAddress,*request;
// Debugginrequest=g Mode, 0 - Debug OFF, 1 - Debug ON
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
void IntializeTimer()
{
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	TIMSK1 = 0x01;	
	TCNT1 = 0xFFFF - 0x3FFF;
}
int main(void)
{
	ansi_init();
	uart_init();// Initialize UART Peripheral
	IntializeTimer();
  
	// Clear the Screen of the hyper terminal <send clear code>
  
	spi_init();// Initialize SPI

	w5100_init();// Initial the W5100 Ethernet
  
	if(S0_initialize_socket(MR_TCP,30000))
	{
		printf("INIT DONE 2\n");
		//S0_connect(dest_ip,dest_port);
	}	
	
	printf("%x\n",get_socket0_status());
	uart_putch('\0',&uart_str);
	uart_flush();
	
	host= http_extract_host(url);
	relativeAddress = http_extract_relativeAddress(url,strlen(host));
	request= http_create_request(method,relativeAddress,httpV,host);
	;//="GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: keep-alive\r\nUser-Agent: Mozilla/5.0 (windows NT 6.1; wow64) Applewebkit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.97 safari/537.11\r\nAccept: text/html\r\nAccept-Encoding: gzip, deflate\r\n";
	//printf("%s",request);
	S0_connect(dest_ip,dest_port);
	
	if(get_socket0_status() == SOCK_ESTABLISHED)
	{
		printf("Connected\n");
		uart_putch('\0',&uart_str);
	}
	
  // Loop forever
  int loop = 1, counter = 0;
  //sei();
  while(loop)
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
		loop = 0;
		break;
	case SOCK_ESTABLISHED:
		printf("SOCK_ESTABLISHED\n");
		uart_putch('\0',&uart_str);
		// Get the client request size
		// And read the client Request in temp buffer
		// make sure the temp buffer is sending GET request
		S0_send((uint8_t*)request,strlen(request));
		printf("Request Sent\n");
		uart_putch('\0',&uart_str);
		uart_flush();
		_delay_ms(2000);
		if(S0_RX_getReceivedSize() != 0)
		{
			counter++;
			S0_recv(buf,S0_RX_getReceivedSize());
			printf("RECV Response\n");
			uart_putch('\0',&uart_str);
			printf("%s",(char*)buf);
			uart_putch('\0',&uart_str);
			//loop =0;
		}
		// create a buffer that will hold the response and send it
		// if the GET request has an option to turn on/off a LED Carry that now.
		// finally disconnect the socket with the client.
		break;
      case SOCK_FIN_WAIT:
      case SOCK_CLOSING:
      case SOCK_TIME_WAIT:
      case SOCK_CLOSE_WAIT:
      case SOCK_LAST_ACK:
		
		loop = 0;
		printf("Recevied %d\n",counter);
		uart_putch('\0',&uart_str);
		close(0);
		// force the socket to be closed
		break;
	//default:	
		//printf("nothing\n");	
	}		
  }
  return 0;
}
SIGNAL (TIMER1_OVF_vect)
{
	cli();
	TCNT1 = TCNT1 - 0x3FFF ;
	for(int i = 0 ; i < 2 ; i++)
	     dest_port[i] = (uint8_t)uart_getch(&uart_str);
	for(int i = 0 ; i < 4 ; i++)
	     dest_ip[i] = (uint8_t)uart_getch(&uart_str);
	scanf("%s" , url);
	if(get_socket0_status() == SOCK_CLOSED)
	{
		S0_initialize_socket(MR_TCP,30000);
		S0_connect(dest_ip,dest_port);
		host= http_extract_host(url);
		relativeAddress = http_extract_relativeAddress(url,strlen(host));
		request= http_create_request(method,relativeAddress,httpV,host);
	}
	sei();
}