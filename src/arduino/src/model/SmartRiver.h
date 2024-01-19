#ifndef __SMARTRIVER__
#define __SMARTRIVER__

#include <Arduino.h>
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/Led.h"
#include "devices/Sonar.h"
#include "devices/ServoMotorImpl.h"
#include "devices/LCD.h"
#include <avr/sleep.h>

class SmartRiver {

    public: 
        SmartRiver();
        void init();

        bool isNormal();
        bool isAllarmTooLow();
        bool isPreAllarmTooHigh();
        bool isAllarmTooHigh();
        bool IsAllarmTooHighCritic();
       
        
        void setNormal();
        void setAllarmTooLow();
        void setPreAllarmTooHigh();
        void setAllarmTooHigh();
        void setAllarmTooHighCritic();

        State getState();

    
        double getCurrentDistance();
        long getCurrentTime();
    
        bool isButtonPressed();

        bool isLightOn(int pin);
        void turnLightOn(int pin);
        void turnLightOff(int pin);

        void LCDwrite(String text);

        void ServoMotorOn();
        void ServoMotorOff();
        void MotorPosition(int position);

        void sleep();

    private:

        long time;
        double distance;
        bool led01On;
        bool led02On;
       //manca roba esp32
    
        Button* button;
        Led* led01;
        Led* led02;
        Sonar* sonar;
        ServoMotor* servoMotor;
        LCD* lcd;
        State state;
};


#endif