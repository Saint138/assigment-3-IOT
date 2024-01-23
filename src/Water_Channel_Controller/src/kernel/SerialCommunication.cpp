#include "SerialCommunication.h"

#include "config.h"

SmartRiver* SerialCommunication::pSmartRiver;

SerialCommunication::SerialCommunication(SmartRiver* pcw) {
    pSmartRiver = pcw; 
}

void SerialCommunication::init() {
    Serial.begin(9600);
}

void SerialCommunication::update() {
    /*pSmartRiver->getCurrentTemp();
    String msg = stateAsString(pSmartRiver->getState()) + ":" + pSmartRiver->getCurrentTemp() + ":" + pSmartRiver->getCurrentDistance();
    Serial.println(msg);*/
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