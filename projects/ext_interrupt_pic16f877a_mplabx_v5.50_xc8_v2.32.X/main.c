/*
 * PIC16F877A Samples
 * Sample 03: External Interrupts
 * Author: David Nascimento Coelho
 * Last Update: 2021/09/25
 */

// CONFIGURATION BITS

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"

// CONSTANTS

#define _XTAL_FREQ 20000000     // Processor frequency for delay functions

#define bot1 !PORTBbits.RB0     // button at RB0 pin
#define led1 PORTBbits.RB1      // led at RB1 pin

// VARIABLES

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = !led1;
    }
        
}

/* Set all Needed registers */
void init(void)
{
// I/O
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000000;
    PORTE = 0b00000000;

    TRISA = 0b00000000;
    TRISB = 0b00000001;
    TRISC = 0b00000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    OPTION_REG = 0b10000011;
/*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA   (=0 pre-escaler for timer0)
	   			   |||TMR0SE (when using as counter)
	   			   ||TMR0CS  (=0 timer)
	  			   |INTEDG   (int ext / =0 falling edge)
	   			   !PORTB    Pull-up enable (=1 disabled)
*/
    INTCON = 0b00010000;
/*	   		   ||||||||
	   		   |||||||RBIF
	   		   ||||||INTF
	   		   |||||TMR0IF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		//TIMER 1 e 2, AD, Serial... 
	   		   GIE			//are considered peripherals
*/ 
}

/* Main Function */
void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // Infinity loop
    while(1);
    
    return;
}
