/*
 * File:   main.c
 * Purpose: Practice programming PIC chips using MPLAB X environment and PicKit3 programmer.
 * Code works with pic16F616 chip. 
 * Author: paul
 *
 * Created on 18 November 2017, 16:18
 */

#include "configuration.h"

// Define three pins from PortC to use as outputs for LEDs
#define LED0 RC3

int count = 0;

void initMain() {
    // Set ports as digital I/O, not analogue input
    ANSEL = 0b00000000;

    /*
     * TRISC is the data direction register for PORTC.
     * Here we set all pins to be outputs (0)
     */
    TRISC = 0;

    // Set to timer mode (internal clock source)
    OPTION_REGbits.T0CS = 0;

    // Assign Prescaler to TIMER0 instead of WatchDogTimer 
    OPTION_REGbits.PSA = 0;
    // Set Prescaler to 256
    OPTION_REGbits.PS = 0b111;

    // enable Timer0 interrupt
    INTCONbits.T0IE = 1;
    // Enable global interrupts
    INTCONbits.GIE = 1;
}

void main(void) {
    initMain();

    while (1);
}

void interrupt ISR(void) {
    static int count = 0;

    // Reset timer flag
    INTCONbits.T0IF = 0;

    count++;

    // 15 timer counts = 1Hz, 3 counts = 5Hz
    // Given 4MHz osc, 1:256 prescaler, 8-bit Timer (256) with no offset
    // count = 4MHz / 4 / 256 / 256 / 5
    if (count == 3) {
        LED0 = 1;
        count = 0;
    } else {
        LED0 = 0;
    }
}
