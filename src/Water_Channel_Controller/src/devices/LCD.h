#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

class LCD {
    
    public:
        LCD();
        void printText(String text);
        void setCursorDisplay(int x, int y);
        void clearDisplay();
        void video(int val,String text);

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif