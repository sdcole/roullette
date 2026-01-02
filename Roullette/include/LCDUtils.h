// lcdUtils.h
#ifndef LCDUTILS_H
#define LCDUTILS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Declare the LCD and functions
extern LiquidCrystal_I2C lcd;

void clearTopRow();
void clearBottomRow();
void setTopText(const char* text);
void setBottomText(const char* text);

#endif // LCDUTILS_H
