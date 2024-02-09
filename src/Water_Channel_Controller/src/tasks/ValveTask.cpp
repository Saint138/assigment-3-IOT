#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(WaterController* waterController, Potentiometer* potentiometer) {
  this->waterController = waterController;
  this->potentiometer = potentiometer;
}
  
void ValveTask::init(int period){
  Task::init(period);
  valvestate = AUTO;
}

void ValveTask::tick(){
  if(waterController->isAutomatic()) {
    valvestate = AUTO;
  } else {
    if(waterController->isDashboard()) {
      valvestate = DASHBOARD;
    } else {
      valvestate = MANUAL;
    }
  }
  
  switch (valvestate){
    int valveOpening;

    case MANUAL:
      valveOpening = map(potentiometer->getValue(), 0, 1023, 0, 100);
      waterController->setValveOpening(valveOpening);
      waterController->MotorPosition(setAngle(valveOpening));
      waterController->LCDwrite(valveOpening, "MANUAL");
    break;

    case DASHBOARD:
      valveOpening = waterController->getValveOpening();
      waterController->MotorPosition(setAngle(valveOpening));
      waterController->LCDwrite(valveOpening, "DASHBOARD");
    break;

    case AUTO:
      /*switch con casi aperture*/
      switch(waterController->getState()){
        case NORMAL:
          valveOpening = 25;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->setValveOpening(valveOpening);
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case PREALLARMTOOHIGH:
          valveOpening = 25;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->setValveOpening(valveOpening);
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGH:
          valveOpening = 50;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->setValveOpening(valveOpening);
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGHCRITIC:
          valveOpening = 100;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->setValveOpening(valveOpening);
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOLOW:
          valveOpening = 0;
          waterController->MotorPosition(setAngle(valveOpening));
          waterController->setValveOpening(valveOpening);
          waterController->LCDwrite(valveOpening, "AUTOMATIC");
          break;

      }
    break;
  }
}

int setAngle(int percentage) {
  return percentage * 180 / 100;
}
