#include "SerialCommunication.h"

#include "config.h"

WaterController* SerialCommunication::waterController;

SerialCommunication::SerialCommunication(WaterController* pcw) {
    waterController = pcw; 
}

void SerialCommunication::init() {
    Serial.begin(9600);
}

void SerialCommunication::update() {
    if(isMsgAvailable) {
        String msg = getMsg();

        if(msg == "NORMAL") {
            waterController->setNormal();
        } else if(msg == "ALLARMTOOHIGH") {
            waterController->setAllarmTooHigh();
        } else if(msg == "ALLARMTOOHIGHCRITIC") {
            waterController->setAllarmTooHighCritic();
        } else if(msg == "PREALLARMTOOHIGH") {
            waterController->setPreAllarmTooHigh();
        } else if(msg == "ALLARMTOOLOW") {
            waterController->setAllarmTooLow();
        }
    }
}

bool SerialCommunication::isMsgAvailable() {
    return Serial.available() > 0;
}

String SerialCommunication::getMsg() {
    String msg = "";
    char c;
  
    while (Serial.available() > 0 && (c = Serial.read()) != '\n') {
        msg += c;
    }
  
    return msg;
}


String SerialCommunication::stateAsString(State currentState) {
    String msg;
    switch(currentState) {
        case NORMAL:
            msg = "NORMAL";
            break;
        case ALLARMTOOLOW:
            msg = "ALLARMTOOLOW";
            break;
        case ALLARMTOOHIGH:
            msg = "ALLARMTOHIGH";
            break;
        case ALLARMTOOHIGHCRITIC:
            msg = "ALLARTMOOHIGHCRITIC";
            break;
        case PREALLARMTOOHIGH:
            msg = "PREALLARMTOOHIGH";
        default:
            msg = "";
    }
    return msg;
}