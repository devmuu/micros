/*
 * PIC16F877A Samples
 * Serial Communication Library
 * Author: David Nascimento Coelho
 * Last Update: 2018/05/11
 */

#ifndef USART_H
#define	USART_H
#endif	/* USART_H */

// FUNCTIONS

void putch(unsigned char byte);
void send_str( const char * str);
unsigned char getch();
unsigned char getche(void);
