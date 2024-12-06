#ifndef LCD_H
#define LCD_H

#include <pic.h>

// Define LCD control pins
#define rs RC0
#define rw RC1
#define e RC2

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(const char *s);

#endif