#include "WaterController.h"

WaterController::WaterController(Button* button, ServoMotor* servoMotor, LCD* lcd) {
    this->button = button;
    this->servoMotor = servoMotor;
    this->lcd = lcd;
    this->init();
}

void WaterController::init(){
    servoMotor->on();
    servoMotor->setPosition(25);
    State state;
    this->automatic = true;
    this->dashboard = false;
    this->valveOpening = 25;
    this->setNormal();
}

void WaterController::setNormal(){
    state = NORMAL;
}

void WaterController::setAllarmTooHigh(){
    state = ALLARMTOOHIGH;
}

void WaterController::setPreAllarmTooHigh(){
    state = PREALLARMTOOHIGH;
    
}

void WaterController::setAllarmTooHighCritic(){
    state = ALLARMTOOHIGHCRITIC;
}

void WaterController::setAllarmTooLow(){
    state = ALLARMTOOLOW;
}

State WaterController::getState() {
    return state;
}

String WaterController::stateAsString() {
    String msg;
    switch(state) {
        case NORMAL:
            msg = "NORMAL";
            break;
        case ALLARMTOOHIGH:
            msg = "ALLARM-TOO-HIGH";
            break;
        case PREALLARMTOOHIGH:
            msg = "PRE-ALLARM-TOO-HIGH";
            break;
        case ALLARMTOOHIGHCRITIC:
            msg = "ALLARM-TOO-HIGH-CRITIC";
            break;
        case ALLARMTOOLOW:
            msg = "ALLARM-TOO-LOW";
            break;
    }
    return msg;
}

long WaterController::getCurrentTime(){
    return time;
}

int WaterController::getValveOpening(){
    return valveOpening;
}

bool WaterController::isAutomatic(){
    return automatic;
}

bool WaterController::isDashboard(){
    return dashboard;
}

void WaterController::setValveOpening(int valveOpening){
    this->valveOpening = valveOpening;
}

void WaterController::setAutomatic(bool automatic){
    this->automatic = automatic;
}

void WaterController::setDashboard(bool dashboard){
    this->dashboard = dashboard;
}

bool WaterController::isButtonClicked(){
    button->sync();
    return button->isPressed();
}

void WaterController::LCDwrite(int valve, String msg){
    lcd->clearDisplay();
    lcd->video(valve, msg);
}

void WaterController::ServoMotorOn(){
    servoMotor->on();
}

void WaterController::ServoMotorOff(){
    servoMotor->off();
}

void WaterController::MotorPosition(int position){
    servoMotor->setPosition(position);
}
