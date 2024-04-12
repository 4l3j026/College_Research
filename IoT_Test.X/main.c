/*
 * File:   main.c
 * Author: Alejo
 *
 * Created on April 10, 2024, 6:09 PM
 */


#include <xc.h>
#include "Fuses_Configuration.h"
#include "LCD_Library.h"

//Functions 
void Configurations(void);

//Variables 
unsigned char Rx_Buffer;

void main(void) {

    Configurations();
    Init_LCD();
    Send_Instruction_Data(Set, CLR);
    Send_Instruction_Data(Set, ROW1);
    Send_String("ESP12F Test Data");

    while (1) {



    }

}

void Configurations(void) {

    OSCCON = 0x72; //Internal oscillator 
    //Set pins as digital
    ANSELC = 0;
    ANSELD = 0;


    //Set pins as outputs
    TRISCbits.RC4 = 0; //Pins to LCD 
    TRISCbits.RC5 = 0;
    TRISD = 0; //Pins configuration to LCD and Motor driver. 

    //Clean pins 
    LATCbits.LC4 = 0;
    LATCbits.LC5 = 0;
    LATD = 0;

    //---- Interrupts Configurations ----
    INTCONbits.GIE = 1; //Global Interrupt Enabled. 
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enabled. 
    RCONbits.IPEN = 1; //Interrupt Priority Enabled. 

    PIE1bits.RC1IE = 1; //Receive Enabled. 
    PIR1bits.RC1IF = 0; //Receive Flag cleared. 

    //---- EUSART Configurations ----
    SPBRG = 103; //Configuration 9600 bauds. 
    TRISCbits.RC6 = 1; //Enable pin RC6 (TX1).
    TRISCbits.RC7 = 1; //Enable pin RC7 (RX1).

    //---- Transmitter configuration TXSTA1 (TX). 
    TXSTA1bits.TX91 = 0; //9 bits transmitter disabled. 
    TXSTA1bits.TXEN1 = 1; //Transmit Enabled. 
    TXSTA1bits.SYNC1 = 0; //Asynchronous mode. 
    TXSTA1bits.BRGH1 = 1; //High baud rate. 

    //---- Receive configuration RCSTA1 register (RX).
    RCSTAbits.SPEN1 = 1; //Serial port enable bit. 
    RCSTAbits.RX91 = 0; //9 bits transmitter disabled. 
    RCSTAbits.CREN1 = 1; //Receive continuous enabled. 

    //---- Baud configuration BAUDCON1. 
    BAUDCON1bits.BRG16 = 0; //16 bits mode disabled. 

    /*
     
     Remember data buffers. 
     * 
        RCREG1; ----> Receive buffer.
        TXREG1; ----> Transmitter buffer.
      
     */

}

void __interrupt() Reception(void) {

    if (PIR1bits.RC1IF) { //Check interrupt has been activated. 

        Rx_Buffer = RCREG1; //Assign RCREG1 buffer to clean the flag.

        if (Rx_Buffer == 'a') {

            Send_Instruction_Data(Set, CLR);
            Send_Instruction_Data(Set, ROW2);
            Send_Instruction_Data(Write, 'a');

        } else if (Rx_Buffer == 'b') {

            Send_Instruction_Data(Set, CLR);
            Send_Instruction_Data(Set, ROW3);
            Send_Instruction_Data(Write, 'b');

        }

    }

}