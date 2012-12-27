/*
 * uart.c
 *
 * Created: 12/22/2011 9:43:49 AM
 *  Author: Administrator
 */ 

#include "uart.h"

void uart_init(void)
{
   DDRD |= _BV(1) ;	// enable TX output
    /* UBRR0H = HI(baud); UBRR0L = LO(baud) */
    UBRR0 = 103;
    /* Asynchronous mode, no parity, 1-stop bit, 8-bit data */
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00 );

    /* no 2x mode, no multi-processor mode */
    UCSR0A = 0x00;

    /* interrupts disabled, rx and tx enabled, 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void uart_flush(void)
{
  unsigned char dummy;
  while (UCSR0A & (1<<RXC0)) dummy = UDR0;
}

int uart_putch(char ch,FILE *stream)
{
   if (ch == '\n')
    uart_putch('\r', stream);
   while (!(UCSR0A & (1<<UDRE0)));
   UDR0=ch;
   return 0;
}

int uart_getch(FILE *stream)
{
   unsigned char ch;
   while (!(UCSR0A & (1<<RXC0)));
   ch=UDR0;  

   /* Echo the Output Back to terminal */
   uart_putch(ch,stream);       

   return ch;
}