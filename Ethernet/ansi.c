/*
 * ansi.c
 *
 * Created: 12/22/2011 10:06:17 AM
 *  Author: Administrator
 */ 

#include "ansi.h"

void ansi_init(void)
{
	// Define Output/Input Stream
	stdout = stdin = &uart_str;
}

void ansi_cl(void)
{
  // ANSI clear screen: cl=\E[H\E[J
  putchar(27);
  putchar('[');
  putchar('H');
  putchar(27);
  putchar('[');
  putchar('J');
}

void ansi_me(void)
{
  // ANSI turn off all attribute: me=\E[0m
  putchar(27);
  putchar('[');
  putchar('0');
  putchar('m');
}