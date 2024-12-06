#include "lcd.h"

#define delay for(int i = 0; i <= 1000; i++) // Basic delay

void lcd_init() {
    cmd(0x38); // 2-line, 5x7 matrix
    cmd(0x0C); // Display ON, Cursor OFF
    cmd(0x06); // Increment cursor
    cmd(0x80); // Force cursor to beginning
}

void cmd(unsigned char a) {
    PORTB = a;
    rs = 0; // Command mode
    rw = 0; // Write mode
    e = 1;
    delay;
    e = 0;
}

void dat(unsigned char b) {
    PORTB = b;
    rs = 1; // Data mode
    rw = 0; // Write mode
    e = 1;
    delay;
    e = 0;
}

void show(const char *s) {
    while (*s) {
        dat(*s++);
    }
}