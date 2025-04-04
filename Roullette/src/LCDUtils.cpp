// lcdUtils.cpp
#include "LCDUtils.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
//Clears top row of the lcd
void clearTopRow() {
    lcd.setCursor(0, 0);
    lcd.print("                ");
}
//Clears bottom row of the lcd
void clearBottomRow() {
    lcd.setCursor(0, 1);
    lcd.print("                ");
}
/*  Passed string shows up on the top row of lcd
*   const char* -- this is the pointer to the passed char[]
*/
void setTopText(const char* text) {
    clearTopRow();
    lcd.setCursor(0, 0);
    lcd.print(text);
}
/*  Passed string shows up on the bottom row of lcd
*   const char* -- this is the pointer to the passed char[]
*/
void setBottomText(const char* text) {
    clearBottomRow();
    lcd.setCursor(0, 1);
    lcd.print(text);
}
