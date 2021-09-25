/*
 * PIC16F877A Samples
 * Sample 14: Stepper Motor
 * Author: David Nascimento Coelho
 * Last Update: 2018/05/11
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{

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
    TRISC = 0b10000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    
    OPTION_REG = 0b10000001;
 /*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA (=0 pre-escaler para timer0)
	   			   |||TMR0SE (qdo como contador)
	   			   ||TMR0CS (=0 timer)
	  			   |INTEDG (int ext / =0 falling edge)
	   			   !PORTB Pull-up enable (=1 disabled)
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
	   		   GIE			//sao considerados perifericos
*/    

}

void complete_step(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(500);
    // Pos2
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(500);
    // Pos3
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(500);
    // Pos4
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(500);
}
void half_step(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(500);
    // Pos2
    IN1 = 1; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(500);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(500);
    // Pos4
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(500);
    // Pos5
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(500);
    // Pos6
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 1;
    __delay_ms(500);
    // Pos7
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(500);
    // Pos8
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(500);
}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;

    // infinity loop
    while(1)
    {
        complete_step();
        half_step();
    }
    return;
}
