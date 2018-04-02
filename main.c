/*
 * File:   main.c
 * Purpose: Practice programming PIC chips using MPLAB X environment and PicKit3 programmer.
 * Code works with pic16F616 chip. 
 * Author: paul
 *
 * Created on 18 November 2017, 16:18
 */

#include "configuration.h"

void initMain() {
    // Set ports as digital I/O, not analogue input
    ANSEL = 0b00000000;
    
    /*
     * TRISC is the data direction register for PORTC.
     * Here we set all pins to be outputs (0)
     */
    TRISC = 0;
    
    // Turn on Timer2 - this Timer is used by the CCP module's PWM mode
    T2CONbits.TMR2ON = 1;
    
    // Set Timer2 prescaler value to 1:1
    T2CONbits.T2CKPS = 0b00;
    
    // Set Timer 2 period value
    PR2 = 255;
    
    // Select CCP PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // Set 2 LSBs of PWM duty cycle
    CCP1CONbits.DCB = 0b00;
}

void main(void) {
    initMain();
    
    int i = 0;
    
    while(1) {
        // Set 8 MSBs of PWM duty cycle
        CCPR1L = i;
        i++;
        if (i > 255) {
            i = 0;
        }
        __delay_ms(10);
    }
}
