/*
 * PIC16F877A Samples
 * Sample 04: 7-segment display
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

#define ac_disp1 PORTBbits.RB2  // common pin of display 1
#define ac_disp2 PORTBbits.RB3  // common pin of display 2
#define ac_disp3 PORTBbits.RB4  // common pin of display 3
#define ac_disp4 PORTBbits.RB5  // common pin of display 4

#define disp7seg PORTC          // 7 segments connected at portc

// VARIABLES

unsigned char disp1_val = 0;    // current value of display 1
unsigned char disp2_val = 0;    // current value of display 2
unsigned char disp3_val = 0;    // current value of display 3
unsigned char disp4_val = 0;    // current value of display 4

/* vector position corresponds to each number */
const char tab1[16] = 
{
	//PGFEDCBA    => bits related to each segment
	0b00111111,   //OH - 0 
	0b00000110,   //1H - 1 
	0b01011011,   //2H - 2
	0b01001111,   //3H - 3
	0b01100110,   //4H - 4
	0b01101101,   //5H - 5
	0b01111101,   //6H - 6
	0b00000111,   //7H - 7
	0b01111111,   //8H - 8
	0b01101111,   //9H - 9
	0b01110111,   //AH - A
	0b01111100,   //BH - B
	0b00111001,   //CH - C
	0b01011110,   //DH - D
	0b01111001,   //EH - E
	0b01110001,   //FH - F
};
/* another way of defining the same table */
// tab1[16] = {0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x77,0x7c,0x39,0x5e,0x79,0x71};

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {

    INTCONbits.INTF = 0;
    
    disp1_val = disp1_val+1;
	if (disp1_val == 10)
	{
		disp1_val = 0;
		disp2_val = disp2_val+1;
		if (disp2_val == 10)
		{
			disp2_val = 0;
			disp3_val = disp3_val+1;
			if (disp3_val == 10)
			{
				disp3_val = 0;
				disp4_val = disp4_val+1;
				if (disp4_val == 10)
				{
					disp4_val = 0;
				}
			}
		}
	}
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
        // display multiplexing
        disp7seg = tab1[disp1_val];
        ac_disp1 = 1;
        __delay_ms(50);
        ac_disp1 = 0;
        disp7seg = tab1[disp2_val];
        ac_disp2 = 1;
        __delay_ms(50);
        ac_disp2 = 0;
        disp7seg = tab1[disp3_val];
        ac_disp3 = 1;
        __delay_ms(50);
        ac_disp3 = 0;
        disp7seg = tab1[disp4_val];
        ac_disp4 = 1;
        __delay_ms(50);
        ac_disp4 = 0;
    }    
    
    return;
}
