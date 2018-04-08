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
#define LED1 RC4
#define LED2 RC5

void initMain() {
    /*
     * Configure IO
     */
    // Set all ports as digital I/O, except AN0 which is set to analog input
    ANSEL = 0b00000001;
    // Set RA0 to be an input and all other PORTA pins to be outputs 
    TRISA = 0b00000001;
    // Set all PORTA pins to be outputs
    TRISC = 0;

    /*
     * Configure ADC
     */
    // Set conversion clock to Fosc/8
    ADCON1bits.ADCS = 0b001;
    // Set ADC results to be right justified (MSB in ADRESH)
    ADCON0bits.ADFM = 1;
    // Set Vref+ to Vdd
    ADCON0bits.VCFG = 0;
    // Set input channel to AN0
    ADCON0bits.CHS = 0b0000;
    // Zero ADC output variables
    ADRESL = 0;
    ADRESH = 0;
    
    /*
     * Configure interrupt
     */
    // Clear ADC interrupt flag
    PIR1bits.ADIF = 0;
    // Enable ADC interrupts
    PIE1bits.ADIE = 1;
    // Enable peripheral interrupts
    INTCONbits.PEIE = 1;
    // Enable global interrupts
    INTCONbits.GIE = 1;
}

void main(void) {
    initMain();

    while (1) {
        // enable ADC, begin acquiring input voltage
        ADCON0bits.ADON = 1;
        // wait for minimum acquisition time
        __delay_us(10);
        // start conversion of acquired voltage
        ADCON0bits.GO = 1;
    }
}

void interrupt ISR(void) {
    // if an ADC conversion result is ready
    if (PIE1bits.ADIE && PIR1bits.ADIF) {
        // Combine result MSB and LSB
        int result = ((ADRESH << 8) + ADRESL);

        if (result <= 300) {
            LED0 = 1;
            LED1 = 0;
            LED2 = 0;
        } else if (result >= 350 && result <= 600) {
            LED0 = 0;
            LED1 = 1;
            LED2 = 0;
        } else if (result >= 650) {
            LED0 = 0;
            LED1 = 0;
            LED2 = 1;
        }
        // Clear ADC interrupt flag
        PIR1bits.ADIF = 0;
    }
}