#include "SmartRiver.h"


SmartRiver::SmartRiver() {
  // TODO Auto-generated constructor stub
}

void SmartRiver::init(){
    button = new ButtonImpl(BUT_1);
    servoMotor = new ServoMotorImpl(SERVO_PIN);
    lcd = new LCD();
    servoMotor->on();
    State state;
    this->setNormal();
}

void SmartRiver::setNormal(){
    state = NORMAL;
}

void SmartRiver::setAllarmTooHigh(){
    state = ALLARMTOOHIGH;
}

void SmartRiver::setPreAllarmTooHigh(){
    state = PREALLARMTOOHIGH;
    
}

void SmartRiver::setAllarmTooHighCritic(){
    state = ALLARMTOOHIGHCRITIC;
}

void SmartRiver::setAllarmTooLow(){
    state = ALLARMTOOLOW;
}

State SmartRiver::getState() {
    return state;
}

long SmartRiver::getCurrentTime(){
    return time;
}

bool SmartRiver::isButtonClicked(){
    button->sync();
    return button->isClicked();
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
