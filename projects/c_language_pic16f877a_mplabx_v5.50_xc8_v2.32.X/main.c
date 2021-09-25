/*
 * PIC16F877A Samples
 * Sample 01: C coding
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

// Another way: #pragma config WDTE = ON, FOSC = XT, CPD = ON, ...

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"
#include <stdint.h>

// CONSTANTS

#define count_min 0b00110011    // binary base
#define count_max 65            // decimal base
#define level_min 025           // octal base
#define level_max 0xFD          // hexadecimal base
#define letter 'A'              // ASCII coding

// VARIABLES

/* access bits and bytes of the same variable - definition */
typedef union
{
	struct
	{
		unsigned bit0 : 1;
		unsigned bit1 : 1;
		unsigned bit2 : 1;
		unsigned bit3 : 1;
		unsigned bit4 : 1;
		unsigned bit5 : 1;
		unsigned bit6 : 1;
		unsigned bit7 : 1;
	}bits;
	char byte;
}generic_byte;

/* access bit and bytes of the same variable - create variable */
generic_byte var1;

/* standard variables */
uint8_t  flag1 = 0;              // 01 bit  - cannot be initialized with "1"
unsigned char letra = 'a';  // 08 bits - from 0 to 255 (ASCII coding)
signed char num1 = 8;       // 08 bits - from -128 to 127
unsigned int acc1 = 300;    // 16 bits - from 0 to 65.535
signed int sum1 = 5000;     // 16 bits - from -32.768 to 32.767
float divisao = 1.3;        // 24 bits - floating point number

/* especial modifiers */
__bank(2) int logEntry;   // indicates in which bank the variable will be stored
__eeprom char title[20];  // indicates that variable will be stored at eeprom
volatile int ad_read;     // variable can be modified several times
const char tabela[] = {0x34,0x56}; // variable will not be modified

// FUNCTIONS

void func_c_coding(void)
{
    // IF-ELSE
    if (flag1 == 1)
    {
        letra = 'd';
    }
    else
    {
        letra = 'e';
    }

   // SWITCH-CASE
    switch(letra)
    {
        case 'a':
            sum1 = 2;
            break;
        case 'b':
            sum1 = 3;
            break;
        default:
            sum1 = 0;
            break;
    }

     // FOR
    for(int i=1; i<=10; i++)
    {
        sum1 = sum1 + 1;
    }

    // WHILE
    while(sum1 < 20)
    {
        sum1 = sum1 + 1;
    }

    // DO-WHILE
    do
    {
        sum1 = sum1 + 1;
    }while(sum1 < 30);

    // Change generic byte variable value
    var1.byte = 0xA2;            // access its byte
    var1.bits.bit0 = 0;          // access its bits
}

void binary_logic(void)
{
    //SHIFT
    num1 = num1 << 1; // shift left (multiply by 2^1)
    num1 = num1 >> 2; // shift right (divide by by 2^2)
    
    // ROTATE
    num1 = (num1 << 1) | (num1 >> 7); // rotate left
    num1 = (num1 >> 1) | (num1 << 7); // rotate right
    
    // XOR ^ (reverse bit value)
    num1 = num1 ^ 0b00100000; // reverses bit 5 of num1
    
    // OR | (set bit)
    num1 = num1 | 0b00000001; // set bit 0 of num1
    
    // AND & (clr bit)
    num1 = num1 & 0b11111101; // clear bit 1 of num1
    
    // AND & (verify bit)
    if (num1 & 0b01000000); // verifies bit 6 of num1
}

void assembly_inst(void)
{
    // assembly commands (already implemented in the compiler)

    //NOP();      // do nothing in 1 machine cycle
    //CLRWDT();   // restart watchdog counting
    //SLEEP();    // enter sleep mode
    //RESET();    // resets device

    // inline assembly instructions - examples

    //asm("NOP");
    //asm("MOVLW 20");
    //asm("MOVWF _i");
    //asm("CLRF Ii+1");
}

// MAIN FUNCTION

void main(void) 
{
    // call functions
    func_c_coding();
    binary_logic();
    assembly_inst();

    // infinity loop
    while(1);

    return;
}
