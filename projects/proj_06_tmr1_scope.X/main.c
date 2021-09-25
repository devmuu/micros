/*
 * PIC16F877A Samples
 * Sample 06: Timer1 and Scope
 * Author: David Nascimento Coelho
 * Last Update: 2018/05/11
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

#define bot1     !PORTBbits.RB0 // button at RB0 pin
#define led1     PORTBbits.RB1  // led at RB1 pin

#define bot1     !PORTBbits.RB0 // button at RB0 pin
#define led1     PORTBbits.RB1  // led at RB1 pin

#define rele1    PORTBbits.RB6  // aciona rele 1
#define out_tmr1 PORTBbits.RB7  // output of timer

#define rec_tmr0 250            // number of tmr0 counts
#define rec_tmr1 1000           // number of tmr1 counts

// VARIABLES

unsigned int count0 = 0;        // timer 0 counter
unsigned int count1 = 0;        // timer 1 counter

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
    
    // Timer0
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF)
    {
         TMR0 = 256 - rec_tmr0;
         count0++;
         INTCONbits.TMR0IF = 0;
    }
    
    // Timer1
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        TMR1 = 65536 - rec_tmr1;
        count1++;
        PIR1bits.TMR1IF = 0;
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
    OPTION_REG = 0b10000001;
 /*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA    (=0 pre-escaler para timer0)
	   			   |||TMR0SE  (qdo como contador)
	   			   ||TMR0CS   (=0 timer)
	  			   |INTEDG    (int ext / =0 falling edge)
	   			   !PORTB Pull-up enable (=1 disabled)
*/
    INTCON = 0b01110000;
/*	   		   ||||||||
	   		   |||||||RBIF
	   		   ||||||INTF
	   		   |||||TMR0IF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		// TIMER 1 e 2, AD, Serial... 
	   		   GIE			// are considered peripherals
*/    
    TMR0 = 256 - rec_tmr0;

// TMR1
    T1CON = 0b00000001;
/*	   		  ||||||||
	   		  |||||||TMR1ON (=1 enable timer1)
	   		  ||||||TMR1CS (=0 internal clock)
     		  |||||T1SYNC (ignored when TMR1CS = 0)
	  		  ||||T1OSCEN (=0 disabled)
	   		  |||T1CKPS0 -> preescaler 1:1 (1, 2, 4, 8)
	   		  ||T1CKPS1 -^
	  		  |unimplemented
	   		  unimplemented 
*/     
    TMR1 = 65536 - rec_tmr1;

    PIE1bits.TMR1IE = 1;

// CCP
    CMCON = 0x07;   // disable compare modules

}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // Infinity loop
    while(1)
    {
        if(count0 == 5000)
        {
            rele1 = !rele1;
            count0 = 0;
        }
        if(count1 == 5000)
        {
            out_tmr1 = !out_tmr1;
            count1 = 0;
        }
        
    }
    
    return;
}
