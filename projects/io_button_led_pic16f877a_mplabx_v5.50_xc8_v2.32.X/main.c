/*
 * PIC16F877A Samples
 * Sample 02: IO ports
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
}

void blink_led(void)
{
    led1 = 1;
    __delay_ms(500);
    led1 = 0;
    __delay_ms(500);         
}

void blink_if_button(void)
{
    if(bot1)
    {
        led1 = 1;
        __delay_ms(500);
        led1 = 0;
        __delay_ms(500);
    }
    else
    {
        led1 = 0;
    }
}

void button_trigger(void)
{
    if(bot1)
    {
        led1 = 1;
        __delay_ms(2000);
        led1 = 0;
    }
}

void main(void) 
{
    // initialization routine
    init();
    
    // Infinity loop
    while(1)
    {
        //blink_if_button();
        blink_led();
        //button_trigger();
    }
    
    return;
}
