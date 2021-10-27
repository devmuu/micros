// CONFIGURAÇÕES GERAIS DO CHIP

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// INCLUDES DE ARQUIVOS

#include "main.h"

// VARIAVEIS

// FUNÇÕES

void init(void)
{
    // IO
    TRISA = 0b00000000;
    TRISB = 0b11110001;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b00000000;
    
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
    INTCON = 0b00011000;
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

void __interrupt() myIsr() 
{  
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = !led1;
    }
    if(INTCONbits.RBIE && INTCONbits.RBIF)
    {
        INTCONbits.RBIF = 0;
        if(!testbit(PORTB,4))
        {
            leds = 0b00000001;
        }
        else if(!testbit(PORTB,5))
        {
            leds = 0b00000010;
        }
        else if(!testbit(PORTB,6))
        {
            leds = 0b00000100;
        }
        else if(!testbit(PORTB,7))
        {
            leds = 0b00001000;
        }
        else
        {
            leds = leds;
        }
    }
}


// FUNÇÃO PRINCIPAL

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // Initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;

    // Main loop
    while(1)
    {
        
    }
    
    return;
}