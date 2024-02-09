#include "ValveTask.h"
#include "StateTask.h"

int valveOpening;

ValveTask::ValveTask(WaterController* waterController, Potentiometer* potentiometer) {
  this->waterController = waterController;
  this->potentiometer = potentiometer;
}
  
void ValveTask::init(int period){
  Task::init(period);
  valvestate = AUTO;
}

void ValveTask::tick(){
  if(automatic) {
    valvestate = AUTO;
  } else {
    if(dashboard) {
      valvestate = DASHBOARD;
    } else {
      valvestate = MANUAL;
    }
  }
  
  switch (valvestate){
    case MANUAL:
      valveOpening = map(potentiometer->getValue(), 0, 1023, 0, 100);
      waterController->MotorPosition(setAngle(valveOpening));
      waterController->LCDwrite(valveOpening, "MANUAL");
    break;

    case DASHBOARD:
      waterController->MotorPosition(setAngle(valveOpening));
      waterController->LCDwrite(valveOpening, "DASHBOARD");
    break;

    case AUTO:
      /*switch con casi aperture*/
      switch(waterController->getState()){
        case NORMAL:
          valveOpening = 25;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case PREALLARMTOOHIGH:
          valveOpening = 25;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGH:
          valveOpening = 50;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGHCRITIC:
          valveOpening = 100;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOLOW:
          valveOpening = 0;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
          break;

      }
    Serial.println("stato cambiato:" + waterController->stateAsString());
    break;
  }
}

int setAngle(int percentage) {
  return percentage * 180 / 100;
}
