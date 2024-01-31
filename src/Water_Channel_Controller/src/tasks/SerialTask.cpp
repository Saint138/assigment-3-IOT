#include "SerialTask.h"

void SerialTask::init(int period) {
  Task::init(period);
}

void SerialTask::tick() {
  if (isMsgAvailable()) {
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

    StaticJsonDocument<112> body;
    StaticJsonDocument<112> data;

    deserializeJson(body, msg);

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
