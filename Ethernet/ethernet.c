/*
 * ethernet.c
 *
 * Created: 12/22/2011 11:50:18 AM
 *  Author: Administrator
 */ 
#include <avr/delay.h>
#include "ethernet.h"
#include "ansi.h"
#include "socket_Utilities.h"

// This method interacts with socket zero only, check socket zero registers in the data sheet to know how to use them
// to accomplish the required tasks.
uint8_t S0_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port)
{
	// this method should close socket zero if it is already closed on client side.
	
	wiznet_write(S0_MR,eth_protocol);// then it should set socket zero mode according to the passed in eth_protocol variable
	
	// then it should define the port number associated with this socket
	uint8_t* ptr_tcp_port = (uint8_t*)&tcp_port;
	wiznet_write(S0_PORT,*ptr_tcp_port);
	wiznet_write(S0_PORT + 1,*(ptr_tcp_port + 1));
	
	wiznet_write(S0_CR,CR_OPEN);// then it should open the socket and wait till it is opened
	
	//while(get_socket0_status() != SOCK_INIT);
	// then it should make sure the socket is initialized correctly and return TRUE in that case
	// in case of failure return FALSE and close the socket just in case!
	if(get_socket0_status() != SOCK_INIT)
			{
				wiznet_write(S0_CR,CR_CLOSE);
				return FALSE;
			}
	printf("INIT DONE 1\n");		
	printf("%x\n",get_socket0_status());		
	uart_putch('\0',&uart_str);		
	return TRUE;						
}
// This method interacts with socket one only, check socket zero registers in the data sheet to know how to use them
// to accomplish the required tasks.
uint8_t S1_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port)
{
	// this method should close socket one if it is already closed on client side.
	
	wiznet_write(S1_MR,eth_protocol);// then it should set socket one mode according to the passed in eth_protocol variable
	
	// then it should define the port number associated with this socket
	uint8_t* ptr_tcp_port = (uint8_t*)&tcp_port;
	wiznet_write(S1_PORT,*ptr_tcp_port);
	wiznet_write(S1_PORT + 1,*(ptr_tcp_port + 1));
	
	wiznet_write(S1_CR,CR_OPEN);// then it should open the socket and wait till it is opened
	//while(get_socket1_status() != SOCK_INIT);
	// then it should make sure the socket is initialized correctly and return TRUE in that case
	// in case of failure return FALSE and close the socket just in case!
	if(get_socket1_status() != SOCK_INIT)
			{
				wiznet_write(S1_CR,CR_CLOSE);
				return FALSE;
			}
	return TRUE;
}
// This method interacts with socket two only, check socket zero registers in the data sheet to know how to use them
// to accomplish the required tasks.
uint8_t S2_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port)
{
	// this method should close socket zero if it is already closed on client side.
	
	wiznet_write(S2_MR,eth_protocol);// then it should set socket two mode according to the passed in eth_protocol variable
	
	// then it should define the port number associated with this socket
	uint8_t* ptr_tcp_port = (uint8_t*)&tcp_port;
	wiznet_write(S2_PORT,*ptr_tcp_port);
	wiznet_write(S2_PORT + 1,*(ptr_tcp_port + 1));
	
	wiznet_write(S2_CR,CR_OPEN);// then it should open the socket and wait till it is opened
	//while(get_socket2_status() != SOCK_INIT);
	// then it should make sure the socket is initialized correctly and return TRUE in that case
	// in case of failure return FALSE and close the socket just in case!
	if(get_socket2_status() != SOCK_INIT)
			{
				wiznet_write(S2_CR,CR_CLOSE);
				return FALSE;
			}
	return TRUE;
}
// This method interacts with socket three only, check socket zero registers in the data sheet to know how to use them
// to accomplish the required tasks.
uint8_t S3_initialize_socket(uint8_t eth_protocol,uint16_t tcp_port)
{
	// this method should close socket zero if it is already closed on client side.
	
	wiznet_write(S3_MR,eth_protocol);// then it should set socket three mode according to the passed in eth_protocol variable
	
	// then it should define the port number associated with this socket
	uint8_t* ptr_tcp_port = (uint8_t*)&tcp_port;
	wiznet_write(S3_PORT,*ptr_tcp_port);
	wiznet_write(S3_PORT + 1,*(ptr_tcp_port + 1));
	
	wiznet_write(S3_CR,CR_OPEN);// then it should open the socket and wait till it is opened
	//while(get_socket3_status() != SOCK_INIT);
	// then it should make sure the socket is initialized correctly and return TRUE in that case
	// in case of failure return FALSE and close the socket just in case!
	if(get_socket3_status() != SOCK_INIT)
			{
				wiznet_write(S3_CR,CR_CLOSE);
				return FALSE;
			}
	return TRUE;
}
// This method interacts with all the sockets, check socket 0/1/2/3 registers in the data sheet to know how to use them
// to accomplish the required tasks.
void close(int socket_num)
{
   // send close command the socket n
   // wait till it is already closed.
   switch(socket_num)
   {
	   case 0 :
			wiznet_write(S0_CR,CR_CLOSE); 
			while(get_socket0_status() != SOCK_CLOSED);
			break;
		case 1:
			wiznet_write(S1_CR,CR_CLOSE);
			while(get_socket1_status() != SOCK_CLOSED);
			break;
		case 2:
			wiznet_write(S2_CR,CR_CLOSE);
			while(get_socket2_status() != SOCK_CLOSED);
			break;
		case 3:
			wiznet_write(S3_CR,CR_CLOSE);
			while(get_socket3_status() != SOCK_CLOSED);
			break;
		default:
			break;			
   }
   
}

void disconnect(int socket_num)
{
   // send disconnect command
   // wait till it is already disconnected.
   switch(socket_num)
   {
	   case 0 :
			wiznet_write(S0_CR,CR_DISCON); 
			while(get_socket0_status() != SOCK_CLOSE_WAIT);
			break;
		case 1:
			wiznet_write(S1_CR,CR_DISCON);
			while(get_socket1_status() != SOCK_CLOSE_WAIT);
			break;
		case 2:
			wiznet_write(S2_CR,CR_DISCON);
			while(get_socket2_status() != SOCK_CLOSE_WAIT);
			break;
		case 3:
			wiznet_write(S3_CR,CR_DISCON);
			while(get_socket3_status() != SOCK_CLOSE_WAIT);
			break;
		default:
			break;			
   }
}

uint8_t S0_listen(void)
{
	// make sure socket is already initialized correctly.
	// other wise return zero (FALSE)
	if(get_socket0_status() != SOCK_INIT)
		return FALSE;
	wiznet_write(S0_CR,CR_LISTEN);// send listen command to socket zero
	_delay_ms(1);// wait till it is executed
	return get_socket0_status() == SOCK_LISTEN;// if the socket zero status is changed to listening return one (TRUE)
								// otherwise return zero (FALSE)
}
uint8_t S1_listen(void)
{
	// make sure socket is already initialized correctly.
	// other wise return zero (FALSE)
	if(get_socket1_status() != SOCK_INIT)
		return FALSE;
	wiznet_write(S1_CR,CR_LISTEN);// send listen command to socket one
	_delay_ms(1);// wait till it is executed
	return get_socket1_status() == SOCK_LISTEN;// if the socket one status is changed to listening return one (TRUE)
								// otherwise return zero (FALSE)
}
uint8_t S2_listen(void)
{
	// make sure socket is already initialized correctly.
	// other wise return zero (FALSE)
	if(get_socket2_status() != SOCK_INIT)
		return FALSE;
	wiznet_write(S2_CR,CR_LISTEN);// send listen command to socket two
	_delay_ms(1);// wait till it is executed
	return get_socket2_status() == SOCK_LISTEN;// if the socket two status is changed to listening return one (TRUE)
								// otherwise return zero (FALSE)
}
uint8_t S3_listen(void)
{
	// make sure socket is already initialized correctly.
	// other wise return zero (FALSE)
	if(get_socket3_status() != SOCK_INIT)
		return FALSE;
	wiznet_write(S3_CR,CR_LISTEN);// send listen command to socket three
	_delay_ms(1);// wait till it is executed
	return get_socket3_status() == SOCK_LISTEN;// if the socket three status is changed to listening return one (TRUE)
								// otherwise return zero (FALSE)
}

uint16_t S0_send(const uint8_t *buf,uint16_t buflen)
{
	// given the required data and its length
	// first make sure the transmission buffer on the ship has free space enough to hold your buffer
	if(S0_TX_getFreeSize() < buflen)
	{
		_delay_ms(1000);// otherwise wait 1 ms and try to check the buffer length once again
		if(S0_TX_getFreeSize() < buflen)// maximum for 1 second then return zero (FALSE) to indicate an error (do not forget to disconnect the socket)
		{
			disconnect(0);
			return FALSE;
		}								
	}				
	
	// if there are enough size in the transmission buffer on wiznet ship start sending the data.
	// to do that you have to read the start address of the free space on the wiznet ship first.
	// make a loop to calculate the real address relative to the start address you just got from the wiznet ship
	// refer to the data sheet page 33 example and study it well.
	
	uint16_t BASE = gS0_TX_BASE,TX_WR=S0_TX_getWriteAddress();
	uint16_t offset= TX_WR & gSn_TX_MASK(0);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_TX_MASK(0) + 1;
	/* if overflow socket TX memory*/
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			wiznet_write(BASE + countByte,*(leftBuffer + countByte));
		}
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
	}
	
	TX_WR += buflen;
	
	uint8_t* ptr_TX_WR = (uint8_t*)&TX_WR;
	wiznet_write(S0_TX_WR,*ptr_TX_WR);
	wiznet_write(S0_TX_WR + 1,*(ptr_TX_WR + 1));
	
	wiznet_write(S0_CR,CR_SEND);
	_delay_us(5);
	// finally write back the new start address for the free space on the ship.
	// and send command SEND to the ship so it starts sending the buffer on the wires
	// and wait till it is already sent.
}
uint16_t S1_send(const uint8_t *buf,uint16_t buflen)
{
	// given the required data and its length
	// first make sure the transmission buffer on the ship has free space enough to hold your buffer
	if(S1_TX_getFreeSize() < buflen)
	{
		_delay_ms(1000);// otherwise wait 1 ms and try to check the buffer length once again
		if(S1_TX_getFreeSize() < buflen)// maximum for 1 second then return zero (FALSE) to indicate an error (do not forget to disconnect the socket)
		{
			disconnect(1);
			return FALSE;
		}								
	}				
	
	// if there are enough size in the transmission buffer on wiznet ship start sending the data.
	// to do that you have to read the start address of the free space on the wiznet ship first.
	// make a loop to calculate the real address relative to the start address you just got from the wiznet ship
	// refer to the data sheet page 33 example and study it well.
	
	uint16_t BASE = gS1_TX_BASE,TX_WR=S1_TX_getWriteAddress();
	uint16_t offset= TX_WR & gSn_TX_MASK(1);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_TX_MASK(1) + 1;
	/* if overflow socket TX memory*/
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			wiznet_write(BASE + countByte,*(leftBuffer + countByte));
		}
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
	}
	
	TX_WR += buflen;
	
	uint8_t* ptr_TX_WR = (uint8_t*)&TX_WR;
	wiznet_write(S1_TX_WR,*ptr_TX_WR);
	wiznet_write(S1_TX_WR + 1,*(ptr_TX_WR + 1));
	
	wiznet_write(S1_CR,CR_SEND);
	_delay_us(5);
	// finally write back the new start address for the free space on the ship.
	// and send command SEND to the ship so it starts sending the buffer on the wires
	// and wait till it is already sent.
}
uint16_t S2_send(const uint8_t *buf,uint16_t buflen)
{
	// given the required data and its length
	// first make sure the transmission buffer on the ship has free space enough to hold your buffer
	if(S2_TX_getFreeSize() < buflen)
	{
		_delay_ms(1000);// otherwise wait 1 ms and try to check the buffer length once again
		if(S2_TX_getFreeSize() < buflen)// maximum for 1 second then return zero (FALSE) to indicate an error (do not forget to disconnect the socket)
		{
			disconnect(2);
			return FALSE;
		}								
	}				
	
	// if there are enough size in the transmission buffer on wiznet ship start sending the data.
	// to do that you have to read the start address of the free space on the wiznet ship first.
	// make a loop to calculate the real address relative to the start address you just got from the wiznet ship
	// refer to the data sheet page 33 example and study it well.
	
	uint16_t BASE = gS2_TX_BASE,TX_WR=S2_TX_getWriteAddress();
	uint16_t offset= TX_WR & gSn_TX_MASK(2);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_TX_MASK(2) + 1;
	/* if overflow socket TX memory*/
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			wiznet_write(BASE + countByte,*(leftBuffer + countByte));
		}
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
	}
	
	TX_WR += buflen;
	
	uint8_t* ptr_TX_WR = (uint8_t*)&TX_WR;
	wiznet_write(S2_TX_WR,*ptr_TX_WR);
	wiznet_write(S2_TX_WR + 1,*(ptr_TX_WR + 1));
	
	wiznet_write(S2_CR,CR_SEND);
	_delay_us(5);
	// finally write back the new start address for the free space on the ship.
	// and send command SEND to the ship so it starts sending the buffer on the wires
	// and wait till it is already sent.
}
uint16_t S3_send(const uint8_t *buf,uint16_t buflen)
{
	// given the required data and its length
	// first make sure the transmission buffer on the ship has free space enough to hold your buffer
	if(S3_TX_getFreeSize() < buflen)
	{
		_delay_ms(1000);// otherwise wait 1 ms and try to check the buffer length once again
		if(S3_TX_getFreeSize() < buflen)// maximum for 1 second then return zero (FALSE) to indicate an error (do not forget to disconnect the socket)
		{
			disconnect(3);
			return FALSE;
		}								
	}				
	
	// if there are enough size in the transmission buffer on wiznet ship start sending the data.
	// to do that you have to read the start address of the free space on the wiznet ship first.
	// make a loop to calculate the real address relative to the start address you just got from the wiznet ship
	// refer to the data sheet page 33 example and study it well.
	
	uint16_t BASE = gS3_TX_BASE,TX_WR=S3_TX_getWriteAddress();
	uint16_t offset= TX_WR & gSn_TX_MASK(3);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_TX_MASK(3) + 1;
	/* if overflow socket TX memory*/
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			wiznet_write(BASE + countByte,*(leftBuffer + countByte));
		}
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			wiznet_write(start_physical_address + countByte,*(buf + countByte));
		}
	}
	
	TX_WR += buflen;
	
	uint8_t* ptr_TX_WR = (uint8_t*)&TX_WR;
	wiznet_write(S3_TX_WR,*ptr_TX_WR);
	wiznet_write(S3_TX_WR + 1,*(ptr_TX_WR + 1));
	
	wiznet_write(S3_CR,CR_SEND);
	_delay_us(5);
	
	return TRUE;
	// finally write back the new start address for the free space on the ship.
	// and send command SEND to the ship so it starts sending the buffer on the wires
	// and wait till it is already sent.
}

uint16_t S0_recv(uint8_t *buf,uint16_t buflen)
{
	// make sure the request buffer size is not bigger than the maximum buffer size.
	// otherwise truncate it
	if(buflen >= MAX_BUF)
		buflen = MAX_BUF - 1;
		
	// read the start address of the read buffer on the ship
	uint16_t BASE = gS0_RX_BASE,RX_RD=S0_RX_getReadAddress();
	uint16_t offset= RX_RD & gSn_RX_MASK(0);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_RX_MASK(0) + 1;
	
	// make a loop to read all the bytes and store them in buf[i]
	// write back the reading address to make the ship points to the next unread part of the buffer
	
	// refer back to the example on page 36 of the wiznet data sheet
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			leftBuffer[countByte]=wiznet_read(BASE + countByte);
		}						
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}			
	}		
    
	buf[buflen]='\0'; // add '\0' to make the end of the buffer.
    
	RX_RD += buflen;
	uint8_t* ptr_RX_RD = (uint8_t*)&RX_RD;
	wiznet_write(S0_RX_RD,*ptr_RX_RD);
	wiznet_write(S0_RX_RD + 1,*(ptr_RX_RD + 1));
	
    wiznet_write(S0_CR,CR_RECV);// finally send receive command to the ship and wait for it to process the command
	_delay_us(5);// you can simply wait 5 us to make sure the command is executed.
}
uint16_t S1_recv(uint8_t *buf,uint16_t buflen)
{
	// make sure the request buffer size is not bigger than the maximum buffer size.
	// otherwise truncate it
	if(buflen >= MAX_BUF)
		buflen = MAX_BUF - 1;
		
	// read the start address of the read buffer on the ship
	uint16_t BASE = gS1_RX_BASE,RX_RD=S1_RX_getReadAddress();
	uint16_t offset= RX_RD & gSn_RX_MASK(1);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_RX_MASK(1) + 1;
	
	// make a loop to read all the bytes and store them in buf[i]
	// write back the reading address to make the ship points to the next unread part of the buffer
	
	// refer back to the example on page 36 of the wiznet data sheet
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			leftBuffer[countByte]=wiznet_read(BASE + countByte);
		}						
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}			
	}		
    
	buf[buflen]='\0'; // add '\0' to make the end of the buffer.
    
	RX_RD += buflen;
	uint8_t* ptr_RX_RD = (uint8_t*)&RX_RD;
	wiznet_write(S1_RX_RD,*ptr_RX_RD);
	wiznet_write(S1_RX_RD + 1,*(ptr_RX_RD + 1));
	
    wiznet_write(S1_CR,CR_RECV);// finally send receive command to the ship and wait for it to process the command
	_delay_us(5);// you can simply wait 5 us to make sure the command is executed.
}
uint16_t S2_recv(uint8_t *buf,uint16_t buflen)
{
	// make sure the request buffer size is not bigger than the maximum buffer size.
	// otherwise truncate it
	if(buflen >= MAX_BUF)
		buflen = MAX_BUF - 1;
		
	// read the start address of the read buffer on the ship
	uint16_t BASE = gS2_RX_BASE,RX_RD=S2_RX_getReadAddress();
	uint16_t offset= RX_RD & gSn_RX_MASK(2);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_RX_MASK(2) + 1;
	
	// make a loop to read all the bytes and store them in buf[i]
	// write back the reading address to make the ship points to the next unread part of the buffer
	
	// refer back to the example on page 36 of the wiznet data sheet
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			leftBuffer[countByte]=wiznet_read(BASE + countByte);
		}						
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}			
	}		
    
	buf[buflen]='\0'; // add '\0' to make the end of the buffer.
    
	RX_RD += buflen;
	uint8_t* ptr_RX_RD = (uint8_t*)&RX_RD;
	wiznet_write(S2_RX_RD,*ptr_RX_RD);
	wiznet_write(S2_RX_RD + 1,*(ptr_RX_RD + 1));
	
    wiznet_write(S2_CR,CR_RECV);// finally send receive command to the ship and wait for it to process the command
	_delay_us(5);// you can simply wait 5 us to make sure the command is executed.
}
uint16_t S3_recv(uint8_t *buf,uint16_t buflen)
{
	// make sure the request buffer size is not bigger than the maximum buffer size.
	// otherwise truncate it
	if(buflen >= MAX_BUF)
		buflen = MAX_BUF - 1 ;
		
	// read the start address of the read buffer on the ship
	uint16_t BASE = gS3_RX_BASE,RX_RD=S3_RX_getReadAddress();
	uint16_t offset= RX_RD & gSn_RX_MASK(3);
	uint16_t start_physical_address =  BASE + offset;
	
	uint16_t socket_MaxSize = gSn_RX_MASK(3) + 1;
	
	// make a loop to read all the bytes and store them in buf[i]
	// write back the reading address to make the ship points to the next unread part of the buffer
	
	// refer back to the example on page 36 of the wiznet data sheet
	if(offset + buflen > socket_MaxSize)
	{
		uint16_t upper_size = socket_MaxSize - offset;
		uint16_t countByte;
		for(countByte=0;countByte<upper_size;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}
		uint8_t *leftBuffer = buf + upper_size;
		uint16_t left_size = buflen - upper_size;
		countByte=0;
		for(;countByte<left_size;++countByte)
		{
			leftBuffer[countByte]=wiznet_read(BASE + countByte);
		}						
	}
	else
	{
		uint16_t countByte;
		for(countByte=0;countByte<buflen;++countByte)
		{
			buf[countByte]=wiznet_read(start_physical_address + countByte);
		}			
	}		
    
	buf[buflen]='\0'; // add '\0' to make the end of the buffer.
    
	RX_RD += buflen;
	uint8_t* ptr_RX_RD = (uint8_t*)&RX_RD;
	wiznet_write(S3_RX_RD,*ptr_RX_RD);
	wiznet_write(S3_RX_RD + 1,*(ptr_RX_RD + 1));
	
    wiznet_write(S3_CR,CR_RECV);// finally send receive command to the ship and wait for it to process the command
	_delay_us(5);// you can simply wait 5 us to make sure the command is executed.
}
uint16_t recv_size(void)
{
	// this method should read the socket zero buffer size in wiznet ship.
}

// This method is used to connect with a remote server of the given ip and port via socket 0
void S0_connect(const uint8_t *dest_ip,const uint8_t *dest_port)
{
	wiznet_write(S0_DIPR,dest_ip[0]);
	wiznet_write(S0_DIPR + 1,dest_ip[1]);
	wiznet_write(S0_DIPR + 2,dest_ip[2]);
	wiznet_write(S0_DIPR + 3,dest_ip[3]);
	
	wiznet_write(S0_DPORT,dest_port[0]);
	wiznet_write(S0_DPORT + 1,dest_port[1]);
	
	wiznet_write(S0_CR,CR_CONNECT);
	printf("Connecting with DIPR : %d.%d.%d.%d and DPORT : %d.%d\n",wiznet_read(S0_DIPR),wiznet_read(S0_DIPR+1),
	wiznet_read(S0_DIPR+2),wiznet_read(S0_DIPR+3),wiznet_read(S0_DPORT),wiznet_read(S0_DPORT+1));
	_delay_ms(5);
}
// This method is used to connect with a remote server of the given ip and port via socket 1
void S1_connect(const uint8_t *dest_ip,const uint8_t *dest_port)
{
	wiznet_write(S1_DIPR,dest_ip[0]);
	wiznet_write(S1_DIPR + 1,dest_ip[1]);
	wiznet_write(S1_DIPR + 2,dest_ip[2]);
	wiznet_write(S1_DIPR + 3,dest_ip[3]);
	
	wiznet_write(S1_DPORT,dest_port[0]);
	wiznet_write(S1_DPORT + 1,dest_port[1]);
	
	wiznet_write(S1_CR,CR_CONNECT);
	printf("Connecting with DIPR : %d.%d.%d.%d and DPORT : %d.%d\n",wiznet_read(S1_DIPR),wiznet_read(S1_DIPR+1),
	wiznet_read(S1_DIPR+2),wiznet_read(S1_DIPR+3),wiznet_read(S1_DPORT),wiznet_read(S1_DPORT+1));
}
// This method is used to connect with a remote server of the given ip and port via socket 2
void S2_connect(const uint8_t *dest_ip,const uint8_t *dest_port)
{
	wiznet_write(S2_DIPR,dest_ip[0]);
	wiznet_write(S2_DIPR + 1,dest_ip[1]);
	wiznet_write(S2_DIPR + 2,dest_ip[2]);
	wiznet_write(S2_DIPR + 3,dest_ip[3]);
	
	wiznet_write(S2_DPORT,dest_port[0]);
	wiznet_write(S2_DPORT + 1,dest_port[1]);
	
	wiznet_write(S2_CR,CR_CONNECT);
	printf("Connecting with DIPR : %d.%d.%d.%d and DPORT : %d.%d\n",wiznet_read(S2_DIPR),wiznet_read(S2_DIPR+1),
	wiznet_read(S2_DIPR+2),wiznet_read(S2_DIPR+3),wiznet_read(S2_DPORT),wiznet_read(S2_DPORT+1));
}
// This method is used to connect with a remote server of the given ip and port via socket 3
void S3_connect(const uint8_t *dest_ip,const uint8_t *dest_port)
{
	wiznet_write(S3_DIPR,dest_ip[0]);
	wiznet_write(S3_DIPR + 1,dest_ip[1]);
	wiznet_write(S3_DIPR + 2,dest_ip[2]);
	wiznet_write(S3_DIPR + 3,dest_ip[3]);
	
	wiznet_write(S3_DPORT,dest_port[0]);
	wiznet_write(S3_DPORT + 1,dest_port[1]);
	
	wiznet_write(S3_CR,CR_CONNECT);
	printf("Connecting with DIPR : %d.%d.%d.%d and DPORT : %d.%d\n",wiznet_read(S3_DIPR),wiznet_read(S3_DIPR+1),
	wiznet_read(S3_DIPR+2),wiznet_read(S3_DIPR+3),wiznet_read(S3_DPORT),wiznet_read(S3_DPORT+1));
}
