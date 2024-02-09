#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(ServoMotor* servoMotor, WaterController* waterController, Potentiometer* potentiometer, LCD* lcd) {
  this->servo = servoMotor;
  this->waterController = waterController;
  this->potentiometer = potentiometer;
  this->lcd = lcd;
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
    case AUTO:
      /*switch con casi aperture*/
      switch(waterController->getState()){
        case NORMAL:
          valveOpening = 25;
          servo->setPosition(setAngle(valveOpening));
          lcd->clearDisplay();
          lcd->video(valveOpening, "AUTOMATIC");
        break;

        case PREALLARMTOOHIGH:
          valveOpening = 25;
          servo->setPosition(setAngle(valveOpening));
          lcd->clearDisplay();
          lcd->video(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGH:
          valveOpening = 50;
          servo->setPosition(setAngle(valveOpening));
          lcd->clearDisplay();
          lcd->video(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOHIGHCRITIC:
          valveOpening = 100;
          servo->setPosition(setAngle(valveOpening));
          lcd->clearDisplay();
          lcd->video(valveOpening, "AUTOMATIC");
        break;

        case ALLARMTOOLOW:
          valveOpening = 0;
          servo->setPosition(setAngle(valveOpening)); /*da aggiornare, valore out potenziometro*/
          lcd->clearDisplay();
          lcd->video(valveOpening, "AUTOMATIC");
        break;

      }
    break;

    case MANUAL:
      int valveOpening = map(potentiometer->getValue(), 0, 1023, 0, 100);
      servo->setPosition(setAngle(valveOpening)); /*da aggiornare, valore out potenziometro*/
      lcd->video(valveOpening, "MANUAL");
    break;

    case DASHBOARD:
      servo->setPosition(setAngle(valveOpening)); /*da aggiornare, valore out dashboard*/
      lcd->video(valveOpening, "MANUAL");
    break;
  }

  
}

int setAngle(int percentage) {
    return percentage*180/100;
  }