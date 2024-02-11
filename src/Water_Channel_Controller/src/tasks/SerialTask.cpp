#include "SerialTask.h"

SerialTask::SerialTask(WaterController* waterController) {
    this->waterController = waterController;
}

void SerialTask::init(int period) {
  Task::init(period);
  this->lastMsg = "";
}

void SerialTask::tick() {
    String state;

    if (isMsgAvailable()) {
        bool automatic;
        bool dashboard;
        String msg = getMsg(); 

        if(waterController->isAutomatic() || waterController->isDashboard()) {
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
                waterController->setValveOpening(msg.toInt());
            }

            waterController->setAutomatic(automatic);
            waterController->setDashboard(dashboard);
            Serial.println(waterController->stateAsString());
        }
    }

    if (waterController->isAutomatic()) {
        state = waterController->stateAsString();
    } else {
        state = String(waterController->getValveOpening());
    }

    String newMsg = "AUTOMATIC: " + String(waterController->isAutomatic() ? "true" : "false") + ", DASHBOARD: " + String(waterController->isDashboard() ? "true" : "false") + ", STATE: " + state;
    if(newMsg != lastMsg) {
        Serial.println(newMsg);
        lastMsg = newMsg;
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
            msg = "ALLARM-TOO-HIGH";
            break;
        case ALLARMTOOHIGHCRITIC:
            msg = "ALLARM-TOO-HIGH-CRITIC";
            break;
        case PREALLARMTOOHIGH:
            msg = "PRE-ALLARM-TOO-HIGH";
            break;
        case ALLARMTOOLOW:
            msg = "ALLARM-TOO-LOW";
            break;
    }
    return msg;
}