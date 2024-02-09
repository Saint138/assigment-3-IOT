#include "SerialTask.h"

SerialTask::SerialTask(WaterController* waterController) {
    this->waterController = waterController;
}

void SerialTask::init(int period) {
  Task::init(period);
}

void SerialTask::tick() {
    if (isMsgAvailable()) {
        String msg = getMsg(); 

        if(msg == stateAsString(NORMAL)) {
            automatic = true;
            dashboard = false;
            waterController->setNormal();
        } else if(msg == stateAsString(ALLARMTOOHIGH)) {
            automatic = true;
            dashboard = false;
            waterController->setAllarmTooHigh();
        } else if(msg == stateAsString(ALLARMTOOHIGHCRITIC)) {
            automatic = true;
            dashboard = false;
            waterController->setAllarmTooHighCritic();
        } else if(msg == stateAsString(PREALLARMTOOHIGH)) {
            automatic = true;
            dashboard = false;
            waterController->setPreAllarmTooHigh();
        } else if(msg == stateAsString(ALLARMTOOLOW)) {
            automatic = true;
            dashboard = false;
            waterController->setAllarmTooLow();
        } else {
            automatic = false;
            dashboard = true;
            valveOpening = msg.toInt();
        }

        Serial.println("AUTOMATIC: " + String(automatic ? "true" : "false") + ", DASHBOARD: " + String(dashboard ? "true" : "false") + ", STATE: " + waterController->stateAsString());
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
        case ALLARMTOOHIGH:
            msg = "ALLARMTOOHIGH";
            break;
        case ALLARMTOOHIGHCRITIC:
            msg = "ALLARMTOOHIGHCRITIC";
            break;
        case PREALLARMTOOHIGH:
            msg = "PREALLARMTOOHIGH";
            break;
        case ALLARMTOOLOW:
            msg = "ALLARMTOOLOW";
            break;
    }
    return msg;
}