#include <pic.h>
#include "lcd.h"

__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

void adc();

void main() {
    TRISB = 0x00;  // Port B is output (for LCD data)
    TRISC = 0x00;  // Port C is output (for LCD control)
    TRISA = 0x07;  // RA0, RA1, and RA2 as input (ADC inputs)

    lcd_init();
    while (1) {
        adc(); // Perform ADC reading and display results
    }
}

void adc() {
    unsigned int adcval1, adcval2, adcval3;
    char text1[10], text3[10];
    float product;

    // Read AN0
    ADCON1 = 0xC0; // Right justified
    ADCON0 = 0x81; // ADC ON, FOSC/64, Channel 0
    GO_nDONE = 1; 
    while (GO_nDONE); 
    adcval1 = ((ADRESH << 8) | ADRESL);
    float value1 = adcval1 * (240.0 / 1023.0);

    // Read AN1
    ADCON0 = 0x89; 
    GO_nDONE = 1; 
    while (GO_nDONE); 
    adcval2 = ((ADRESH << 8) | ADRESL);
    float value2 = adcval2 * (10.0 / 1023.0);

    product = value1 * value2;

    unsigned int int_part = (unsigned int)product;
    unsigned int frac_part = (product - int_part) * 1000;
    text1[0] = (int_part / 1000) + '0';
    text1[1] = ((int_part / 100) % 10) + '0';
    text1[2] = ((int_part / 10) % 10) + '0';
    text1[3] = (int_part % 10) + '0';
    text1[4] = '.';
    //text1[4] = (frac_part / 100) + '0';
    text1[5] = ((frac_part / 10) % 10) + '0';
    text1[6] = (frac_part % 10) + '0';
    text1[7] = '\0';

    // Read AN2
    ADCON0 = 0x91; 
    GO_nDONE = 1; 
    while (GO_nDONE); 
    adcval3 = ((ADRESH << 8) | ADRESL);
    float value3 = adcval3 * (10.0 / 1023.0);

    int_part = (unsigned int)value3;
    frac_part = (value3 - int_part) * 1000;
    //text3[0] = (int_part / 1000) + '0';
    //text3[0] = ((int_part / 100) % 10) + '0';
    text3[0] = ((int_part / 10) % 10) + '0';
    text3[1] = (int_part % 10) + '0';
    text3[2] = '.';
    text3[3] = (frac_part / 100) + '0';
    text3[4] = ((frac_part / 10) % 10) + '0';
    text3[5] = (frac_part % 10) + '0';
    text3[6] = '\0';

    // Display on LCD
    cmd(0x80); // Move to first row
    show("POWER: ");
    show(text1);
    show("W");

    cmd(0xC0); // Move to second row
    show("SPEED: ");
    show(text3);
    show("m/s");
}
