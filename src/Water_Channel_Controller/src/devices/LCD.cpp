#include "LCD.h"

LCD::LCD() {
    lcd.init();
    lcd.backlight();
} 

void LCD::printText(String text) {
    lcd.print(text);
}


void LCD::setCursorDisplay(int x, int y) {
    lcd.setCursor(x, y);
}

void LCD::clearDisplay() {
    lcd.clear();
}

void LCD::video(int val, String text) {
    char buffer[20]; // Assicurati che la dimensione del buffer sia sufficiente
    sprintf(buffer, "Valve: %d %", val);
    
    lcd.setCursor(0, 1);
    lcd.print(buffer);
    
    lcd.setCursor(0, 2);
    lcd.print("Modality: " + text);
}
