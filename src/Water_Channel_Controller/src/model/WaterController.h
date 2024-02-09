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
        int getValveOpening();
        bool isAutomatic();
        bool isDashboard();

        void setValveOpening(int valveOpening);
        void setAutomatic(bool automatic);
        void setDashboard(bool dashboard);
    
        bool isButtonClicked();

        void LCDwrite(int valve, String text);

        void ServoMotorOn();
        void ServoMotorOff();
        void MotorPosition(int position);

    private:
    
        bool automatic;
        bool dashboard;
        int valveOpening;
        double temp;
        long time;
        double distance;
    
        Button* button;
        ServoMotor* servoMotor;
        LCD* lcd;
        State state;
};


#endif