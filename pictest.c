/*
 * File:   pictest.c
 * Purpose: Practice programming PIC chips using MPLAB X environment and PicKit3 programmer.
 * Code works with pic16F616 chip. 
 * Author: paul
 *
 * Created on 18 November 2017, 16:18
 */

// CONFIG
// Important to set chip to use internal oscillator
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 4MHZ    // Internal Oscillator Frequency Select bit (4 MHz)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)

// Using XC compiler
#include <xc.h>
#include	<stdio.h>

// Define which pin to use to blink LED
#define LED0 RA0
#define LED1 RA1

// Must define the oscillator frequency (4MHz) to use functions like __delay_ms
// Can be found in data sheet under "Oscillator Configurations"
#define _XTAL_FREQ 4000000

void main(void) {
    ANSEL = 0x00;   // Set ports as digital I/O, not analog input
    ADCON0 = 0x00;  // Shut off A/D converter
//    CMCON = 0x07;   // Shut off Comparator
    VRCON = 0x00;   // Shut off Voltage Reference
    TRISA = 0x08;  // GP3 input, reset all output
    PORTA = 0x00;    // Make all pins 0
    
    while(1) {
        __delay_ms(500);
        LED0 = 0;
        LED1 = 1;
        __delay_ms(500);
        LED0 = 1;
        LED1 = 0;
    }
}
