#include "SerialTask.h"

void SerialTask::init(int period) {
  Task::init(period);
}

void SerialTask::tick() {
  if (isMsgAvailable()) {
    String msg = getMsg(); 

    if(msg == stateAsString(NORMAL)) {
        automatic = true;
        waterController->setNormal();
    } else if(msg == stateAsString(ALLARMTOOHIGH)) {
        automatic = true;
        waterController->setAllarmTooHigh();
    } else if(msg == stateAsString(ALLARMTOOHIGHCRITIC)) {
        waterController->setAllarmTooHighCritic();
    } else if(msg == stateAsString(PREALLARMTOOHIGH)) {
        automatic = true;
        waterController->setPreAllarmTooHigh();
    } else if(msg == stateAsString(ALLARMTOOLOW)) {
        automatic = true;
        waterController->setAllarmTooLow();
    } else {
        automatic = false;
        valveOpening = msg.toInt();
    }

    StaticJsonDocument<112> data;

    data["automatic"] = automatic;
    data["valveOpening"] = valveOpening;

    serializeJson(data, Serial);
    Serial.println("");
  }
}

bool SerialTask::isMsgAvailable() {
    return Serial.available() > 0;
}

String SerialTask::getMsg() {
    String msg = "";
    char c;
  
    while (Serial.available() > 0 && (c = Serial.read()) != '\n') {
        msg += c;
    }
  
    return msg;
}


String SerialTask::stateAsString(State currentState) {
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
