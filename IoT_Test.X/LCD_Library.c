#include "LCD_Library.h"

//Develop initialize LCD function.

void Init_LCD(void) {

    __delay_ms(100); //Delay set by the manufacturer. 
    Send_Instruction_Data(Set, 0x30); //Data set by the manufacturer. 
    __delay_ms(5); //Delay set by the manufacturer. 
    Send_Instruction_Data(Set, 0x30); //Data set by the manufacturer. 
    __delay_ms(5); //Delay set by the manufacturer. 
    Send_Instruction_Data(Set, 0x30); //Data set by the manufacturer. 
    Send_Instruction_Data(Set, 0x02); //Data set by the manufacturer. 
    Send_Instruction_Data(Set, EMS); //Send entry mode set.
    Send_Instruction_Data(Set, DC); //Send command to Display Control. 
    Send_Instruction_Data(Set, FS); //Send command control.
    Send_Instruction_Data(Set, CLR); //Send clear LCD. 
    __delay_ms(100); //Delay set by the manufacturer. 

}

//Develop LCD function to send data or instruction. 

void Send_Instruction_Data(unsigned char Instruction, unsigned char Data) {

    RS = Instruction; //Enable or disabled the register select to write data, or send instruction set.
    LCD_Instruction(Data >> 4); //Send first the most significant bits
    LCD_Instruction(Data & 0x0F); //Send the least significant bits and clean. 

}
//Develop LCD instruction.

void LCD_Instruction(unsigned char Instruction) {

    EN = 1; //Pin ENabled. 
    __delay_us(150); //Wait for the instruction. 
    LATD = Instruction; //Send Instruction to the port. 
    __delay_us(150); //Wait for the instruction. 
    EN = 0; //Pin disabled.
    __delay_us(150); //Wait for the instruction. 

}

//Develop send string

void Send_String(unsigned char *String) { //Receiver string data. 

    for (uint8_t i = 0; String[i] != '\0'; i++) { //i from 0, to find null character ('\0'), increment 1. 

        Send_Instruction_Data(Write, String[i]); //Print each character of string. 

    }

}
