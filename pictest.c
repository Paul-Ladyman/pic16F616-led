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
#include <stdio.h>

// Define which pin to use to blink LED
#define BUTTON0 RA0
#define BUTTON1 RA1
#define BUTTON2 RA2
#define LED0 RC3
#define LED1 RC4
#define LED2 RC5

// Must define the oscillator frequency (4MHz) to use functions like __delay_ms
// Can be found in data sheet under "Oscillator Configurations"
#define _XTAL_FREQ 4000000

void main(void) {
    ANSEL = 0b00000000;   // Set ports as digital I/O, not analog input
    ADCON0 = 0b00000000;  // Shut off A/D converter
    CM1CON0 = 0b00000000;   // Shut off Comparator
    CM2CON0 = 0b00000000;   // Shut off Comparator
    VRCON = 0b00000000;   // Shut off Voltage Reference
    /* 
     * TRISA is the data direction register for PORTA.
     * Here we set RA0 to be a digital input
     * and all other pins to be outputs (0)
     */
    TRISA = 0b00000111;
    PORTA = 0b00000000;    // Make all pins 0
    // TRISC is the data direction register for PORTC.
    // Here we set all pins to be outputs (0)
    TRISC = 0b00000000;
    PORTC = 0b00000000;    // Make all pins 0
    
    while(1) {
        // Read digital state of input
        // the state is inverted since inputs are active low
        int state0 = !BUTTON0;
        int state1 = !BUTTON1;
        int state2 = !BUTTON2;
        LED0 = state0;
        LED1 = state1;
        LED2 = state2;
    }
}
