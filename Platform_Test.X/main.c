///*
// * File:   main.c
// * Author: Alejandro
// *
// * Created on May 2, 2023, 8:34 PM
// */
//
//
//#include <xc.h>
//
//void main(void) {
//    return;
//}


//Alejandro Suarez
//20:24 (hace 4 minutos)
//para m�

#include <xc.h>
#include <string.h>
#include <stdio.h>

// Configuraci�n de bits de configuraci�n
#pragma config FOSC = INTIO67  // Frecuencia del oscilador interno
#pragma config WDTEN = OFF     // Desactiva el watchdog timer
#pragma config LVP = OFF       // Desactiva la programaci�n en bajo voltaje

// Definici�n de frecuencia del oscilador interno
#define _XTAL_FREQ 16000000

// Definici�n de tiempo de espera para la comunicaci�n con LCD
#define time 10

// Constantes para comandos de LCD
#define CD 0x01 // Comando para borrar la pantalla
#define RH 0x02 // Comando para regresar el cursor a la posici�n inicial
#define EMS 0x06 // Comando para mover el cursor hacia la derecha despu�s de escribir
#define DC 0x0F // Comando para encender el display y mostrar el cursor
#define DSr 0x1C // Comando para mover el cursor hacia la derecha
#define DSl 0x18 // Comando para mover el cursor hacia la izquierda
#define FS 0x28 // Comando para establecer la funci�n del display
#define RAW1 0x80 // Comando para establecer la primera l�nea del display
#define RAW2 0xC0 // Comando para establecer la segunda l�nea del display

// Definici�n de pines para control de LCD
#define E LATE0 // Puerto para habilitar el LCD
#define RS LATE1 // Puerto para seleccionar el registro de control o datos del LCD

// Prototipos de funciones
void settings(void);
// Funciones para el control del LCD
void SettingsLCD(unsigned char word);
void WriteLCD(unsigned char word);
void LCD(unsigned char word);
void DataLCD(void);
void Data1LCD(void);
// Funci�n de interrupci�n
void __interrupt() RXTX(void);

// Variables globales
unsigned char d, servo;
char textx[40] = {"coordenadas iniciales X/Y"}; // Texto para mostrar en el LCD
char texty[40] = {"coordenadas finales X/Y"};
int confir, i;
int flag = 0;
float a, b = 0.0, c = 0.0;
char text[20], text2[20];

// Funci�n principal

void main(void) {
    settings(); // Configuraci�n inicial del sistema(perifericos)

 // Ciclo infinito
    while (1) {
 // Pedir coordenadas mediante m�todo seleccionado
        if (flag == 0) {
            printf("Seleccione el metodo de entrada de coordenadas:\n");
            printf("1. Automatico\n");
            printf("2. Semiautomatico\n");
            printf("3. Manual\n");
            flag = 1;
        } else {
            printf("\nSeleccione una opcion: ");
            scanf("%d", &confir);
            if (confir == 1) {
                // M�todo autom�tico
                printf("\nIngrese las coordenadas iniciales X/Y separadas por una coma: ");
                scanf("%f,%f", &a, &b);
                printf("\nIngrese las coordenadas finales X/Y separadas por una coma: ");
                scanf("%f,%f", &c, &b);
                flag = 0;
            } else if (confir == 2) {
                // M�todo semiautom�tico
                printf("\nIngrese las coordenadas iniciales X: ");
                scanf("%f", &a);
                printf("\nPresione una tecla para continuar...");
                getchar();
                printf("\nIngrese las coordenadas iniciales Y: ");
                scanf("%f", &b);
                printf("\nPresione una tecla para continuar...");
                getchar();
                printf("\nIngrese las coordenadas finales X: ");
                scanf("%f", &c);
                printf("\nPresione una tecla para continuar...");
                getchar();
                printf("\nIngrese las coordenadas finales Y: ");
                scanf("%f", &b);
                flag = 0;
            } else if (confir == 3) {
                // M�todo manual
                printf("\nIngrese las coordenadas iniciales X: ");
                scanf("%f", &a);
                printf("\nIngrese las coordenadas iniciales Y: ");
                scanf("%f", &b);
                printf("\nIngrese las coordenadas finales X: ");
                scanf("%f", &c);
                printf("\nIngrese las coordenadas finales Y: ");
                scanf("%f", &b);
                flag = 0;
            } else {
                printf("\nOpci�n inv�lida.
// Actualizaci�n de la pantalla LCD
        DataLCD(); // Mostrar texto en el LCD
        Data1LCD();
    }
}

// Funci�n de configuraci�n de perif�ricos
void settings(void) {

 // Configuraci�n de frecuencia del oscilador interno
    OSCCON = 0x72; // Configuraci�n del oscilador a 16MHz
 // Configuraci�n de pines de entrada/salida

    ANSELC = 0x00; // Configuraci�n del puerto C como digital
    ANSELD = 0x00; // Configuraci�n del puerto D como digital
    ANSELE = 0x00; // Configuraci�n del puerto E como digital
    TRISCbits.RC5 = 0; // Configuraci�n del pin RC5 como salida
    LATCbits.LC5 = 0; // Inicializaci�n del pin RC5 en 0
    TRISD = 0x00; // Configuraci�n del puerto D como salida
    TRISE = 0x00; // Configuraci�n del puerto E como salida
    LATD = 0x00; // Inicializaci�n del puerto D en 0
    LATE = 0x00; // Inicializaci�n del puerto E en 0

// Configuraci�n del LCD
SettingsLCD(0x02);   // Setear la direcci�n de inicio a la posici�n 0, 0
SettingsLCD(EMS);    // Setear el modo de entrada a modo de incremento autom�tico
SettingsLCD(DC);     // Encender la pantalla y el cursor
SettingsLCD(FS);     // Setear la interfaz de datos a 4 bits

// Configuraci�n de la comunicaci�n UART
TRISCbits.RC7 = 1;
TRISCbits.RC6 = 0;
SPBRG1 = 0x19;       // Setear el valor de baud rate a 9600bps
RCSTA1 = 0x90;       // Habilitar la recepci�n en modo as�ncrono
TXSTA1 = 0x20;       // Habilitar la transmisi�n en modo as�ncrono

// Configuraci�n de la interrupci�n
GIE = 1;
PEIE = 1;
RCIE = 1;            // Habilitar la interrupci�n por recepci�n
RCIF = 0;            // Limpiar la bandera de interrupci�n por recepci�n
}

//
void SettingsLCD(unsigned char word) {
    RS = 0;
    LCD(word >> 4);
    LCD(word & 0x0F);
}

void WriteLCD(unsigned char word) {
    RS = 1;
    LCD(word >> 4);
    LCD(word & 0x0F);
}

void LCD(unsigned char data) {
    E = 1;
    __delay_us(time);
    LATD = data;
    __delay_us(time);
    E = 0;
    __delay_us(time);
}

void __interrupt() RXTX(void) {
    if (RC1IF) {
        d = RCREG1;
        if (d == 'S') {
            __delay_ms(1000);
            for (i = 0; i <= strlen(textx); i++) {
                while (TX1IF == 0);
                TXREG1 = textx[i];
            }
            while (TX1IF == 0);
            TXREG1 = 0x0D; //
