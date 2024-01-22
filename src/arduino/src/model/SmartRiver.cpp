#include "SmartRiver.h"

volatile bool detectionInSleep = false;

void wake(){
    detectionInSleep = true;
    delay(100);
}

SmartRiver::SmartRiver() {
  // TODO Auto-generated constructor stub
}

void SmartRiver::init(){
    button = new ButtonImpl(BUT_1);
    led01 = new Led(LED_1);
    led02 = new Led(LED_2);
    /*sonar = new Sonar(ECHO_PIN, TRIG_PIN, MAXTIME);*/
    servoMotor = new ServoMotorImpl(SERVO_PIN);
    lcd = new LCD();
    servoMotor->on();
    State state;
    this->setNormal();
}

bool SmartRiver::isNormal(){
    return state == NORMAL;
}

bool SmartRiver::isAllarmTooHigh(){
    return state == ALLARMTOOHIGH;
}

bool SmartRiver::isPreAllarmTooHigh(){
    return state == PREALLARMTOOHIGH;
}

bool SmartRiver::IsAllarmTooHighCritic(){
    return state == ALLARMTOOHIGHCRITIC;
}

bool SmartRiver::isAllarmTooLow(){
    return state == ALLARMTOOLOW;
}

void SmartRiver::setNormal(){
    state = NORMAL;
    
    temp=millis();
    turnLightOn(LED_2);
    LCDwrite("Valve: 25%");

}

void SmartRiver::setAllarmTooHigh(){
    state = ALLARMTOOHIGH;
    LCDwrite("Proceed to the Washing Area");
}

void SmartRiver::setPreAllarmTooHigh(){
    state = PREALLARMTOOHIGH;
    turnLightOn(LED_2);
    LCDwrite("Ready to Wash");
}

void SmartRiver::setAllarmTooHighCritic(){
    state = ALLARMTOOHIGHCRITIC;
}

void SmartRiver::setAllarmTooLow(){
    state = ALLARMTOOLOW;
    LCDwrite("Detected a Problem - Please Wait");
}

State SmartRiver::getState() {
    return state;
}

double SmartRiver::getCurrentDistance(){
    return this->sonar->getDistance();
}

long SmartRiver::getCurrentTime(){
    return time;
}

bool SmartRiver::isButtonPressed(){
    button->sync();
    return button->isPressed();
}

bool SmartRiver::isLightOn(int pin){
    if(pin == LED_1){
        return led01On;
    }else if(pin == LED_2){
        return led02On;
    }
    return false;
}

void SmartRiver::turnLightOn(int pin){
    if(pin == LED_1){
        led01->switchOn();
        led01On = true;
    }else if(pin == LED_2){
        led02->switchOn();
        led02On = true;
    }
}

void SmartRiver::turnLightOff(int pin){
    if(pin == LED_1){
        led01->switchOff();
        led01On = false;
    }else if(pin == LED_2){
        led02->switchOff();
        led02On = false;
    }
}

void SmartRiver::LCDwrite(String msg){
    lcd->clearDisplay();
    lcd->setCursorDisplay(0, 0);
    lcd->printText(msg);
}

void SmartRiver::ServoMotorOn(){
    servoMotor->on();
}

void SmartRiver::ServoMotorOff(){
    servoMotor->off();
}

void SmartRiver::MotorPosition(int position){
    servoMotor->setPosition(position);
}
