// PIC16F877A Configuration Bit Settings

#include <xc.h>

#define _XTAL_FREQ 20000000

// CONFIG

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

short z;

void interrupt I2C_Slave_Read()
{ 
    if(PIR1bits.SSPIF == 1)
    {
        SSPCONbits.CKP = 0;
        
        //If overflow or collision
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))
        {
            
            z = SSPBUF;            // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;  // Clear the overflow flag
            SSPCONbits.WCOL = 0;   // Clear the collision bit
            SSPCONbits.CKP = 1;    // 
        }
        
        //If last byte was Address + Write
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) 
        {
            z = SSPBUF;             //
            while(!SSPSTATbits.BF); //
            PORTD = SSPBUF;         //
            SSPCONbits.CKP = 1;     //
        }
        
        //If last byte was Address + Read
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
        {
            z = SSPBUF;             //
            SSPSTATbits.BF = 0;     //
            SSPBUF = PORTB ;        //
            SSPCONbits.CKP = 1;     //
            while(SSPSTATbits.BF);  //
        }
       
        PIR1bits.SSPIF = 0;
    }
}

void I2C_Slave_Init(short address)
{
    SSPSTAT = 0x80;
    SSPADD = address;
    SSPCON = 0x36;
    SSPCON2 = 0x01;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
}

void main()
{
    OPTION_REGbits.nRBPU = 0;
    TRISB = 0b11111111;
    TRISD = 0b00000000;
    PORTD = 0b00000000;
    I2C_Slave_Init(0x30);

    while(1);
}