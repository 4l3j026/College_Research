
/* 
 * File:   LCD_Library
 * Author:  Engineer Daniel Alejandro Reyes León. 
 * Comments: First version of lcd 20x4 library.
 * Revision history:  Monday, February 26, 2024.
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_Library_H
#define	LCD_Library_H

#define _XTAL_FREQ 16000000

#include <xc.h> // include processor files - each processor file is guarded.  

//Instructions or commands of the LCD 
#define CLR 0x01 //Command to clear the LCD. 
#define RH 0x02 //Command to Return to Home that is the first position of the LCD (inside first raw and column).
#define EMS 0x06 //Command Entry Mode Set to use moving direction cursor. 
#define DC 0x0F //Command Display Control to set display, cursor and blink. 
#define DSR 0x1C //Command to control the cursor shift to Right (Display Shift Right).
#define DSL 0x18 //Command to control the cursor shift to Left (Display Shift Left). 
#define FS 0x28 //Command to control the 4(28)/8(38) bits mode, 5x8/5x11 character, 1/2 lines display.
#define ROW1 0X80 //Command to access the address of row 1. 
#define ROW2 0xC0 //Command to access the address of row 2. 
#define ROW3 0X94 //Command to access the address of row 3. 
#define ROW4 0XD4 //Command to access the address of row 4. 
#define Set 0 //Command to configuration an instruction. 
#define Write 1 //Command to write on the LCD. 

//Pins of the LCD 
#define RS LATCbits.LATC4 //Define pin (RC4) Register Select as bit flag.
#define EN LATCbits.LATC5 //Define pin (RC5) Enable as bit flag.

//Prototype Functions.
void Configurations(void); //Function to set registers.
void Init_LCD(void); //Function to initialize the LCD. 
void LCD_Instruction(unsigned char Instruction); //Function to send data or instruction inside LCD.
void Send_Instruction_Data(unsigned char Instruction, unsigned char Data); //Function to enable or disable RS.
void Send_String(unsigned char *String); //Show LCD data. 

#endif	/* XC_HEADER_TEMPLATE_H */

