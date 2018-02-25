/*
 * File:   main.c
 * Purpose: Practice programming PIC chips using MPLAB X environment and PicKit3 programmer.
 * Code works with pic16F616 chip. 
 * Author: paul
 *
 * Created on 18 November 2017, 16:18
 */

#include "configuration.h"

// Define three pins from PortA to use to read buttons
#define BUTTON0 RA0
#define BUTTON1 RA1
#define BUTTON2 RA2
// Define three pins from PortC to use as outputs for LEDs
#define LED0 RC3
#define LED1 RC4
#define LED2 RC5

void initMain() {
    // Set ports as digital I/O, not analogue input
    ANSEL = 0b00000000;

    /* 
     * TRISA is the data direction register for PORTA.
     * Here we set RA0, RA1 and RA2 to be a digital input
     * and all other pins to be outputs (0)
     */
    TRISA = 0b00000111;

    // Enable weak pull-ups globally
    OPTION_REGbits.nRAPU = 0;

    // Enable weak pull-ups for for RA0, RA1, RA2
    WPUA = 0b00000111;
    /*
     * TRISC is the data direction register for PORTC.
     * Here we set all pins to be outputs (0)
     */
    TRISC = 0;

    LED0 = 1;
    
    // Enable external interrupt on change for A0
    //    IOCbits.IOCA0 = 1;
    IOCAbits.IOCA0 = 1;
//    IOCbits.IOC0 = 1;
//    IOCAbits.IOC0 = 1;
    
    // Set external interrupt to trigger on falling edge
    OPTION_REGbits.INTEDG = 0;

    // Clear external interrupt flag
//    INTCONbits.INTF = 0;
    INTCONbits.RAIF = 0;
//    INTCONbits.INTE = 1;
    
    // Enable external interrupts
    INTCONbits.RAIE = 1;
    
    // Enable global interrupts
    INTCONbits.GIE = 1;
}

void main(void) {
    initMain();

    while (1) {
//        LED0 = BUTTON0;
//        LED1 = BUTTON1;
//        LED2 = BUTTON2;
    }
}

void interrupt interruptHandler(void) {
//    INTCONbits.INTF = 0;
    LED0 = ~LED0;
    
    INTCONbits.RAIF = 0;
}
