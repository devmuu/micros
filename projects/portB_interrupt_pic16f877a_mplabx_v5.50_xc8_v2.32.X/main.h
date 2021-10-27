///////////////////////////////////////////////

/* 
 * File: 
 * Author: 
 * Comments: 
 * Revision history: 
 */

///////////////////////////////////////////////

// This is a guard condition so that contents of 
// this file are not included more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

// Processor Files
#include <xc.h> 

// C Files
#include <stdint.h>

#define testbit(var, bit) ((var) & (1 <<(bit)))
#define setbit(var, bit)  ((var) |= (1 << (bit)))
#define clrbit(var, bit)  ((var) &= ~(1 << (bit)))
#define invbit(var,bit) ((var) ^= (1<<(bit)))

#define nivel_max 0xFD
#define letra1 'A'
#define contador 50

#define _XTAL_FREQ 20000000

// Pinos
#define botao1 !PORTBbits.RB0
#define led1    PORTBbits.RB1
#define botao2 !PORTBbits.RB4
#define botao3 !PORTBbits.RB5
#define botao4 !PORTBbits.RB6
#define botao5 !PORTBbits.RB7

#define leds PORTC

///////////////////////////////////////////////

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

///////////////////////////////////////////////
