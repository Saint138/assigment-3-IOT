#ifndef __WATERCONTROLLER__
#define __WATERCONTROLLER__

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "TimerOne.h"
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/ServoMotorImpl.h"
#include "devices/LCD.h"

class WaterController {

    public: 
        WaterController(Button* button, ServoMotor* servoMotor, LCD* lcd);
        void init();
        
        void setNormal();
        void setAllarmTooLow();
        void setPreAllarmTooHigh();
        void setAllarmTooHigh();
        void setAllarmTooHighCritic();

        State getState();
        String stateAsString();

        double getCurrentDistance();
        long getCurrentTime();
    
        bool isButtonClicked();

        void LCDwrite(String text);

        void ServoMotorOn();
        void ServoMotorOff();
        void MotorPosition(int position);

    private:
    
        double temp;
        long time;
        double distance;
    
        Button* button;
        ServoMotor* servoMotor;
        LCD* lcd;
        State state;
};


#endif