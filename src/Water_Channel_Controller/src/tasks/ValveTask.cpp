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
    valvestate = MANUAL;
  }
  
  switch (valvestate){
    case AUTO:
      /*switch con casi aperture*/
      switch(waterController->getState()){
        case NORMAL:
          servo->setPosition(setAngle(25)); /*da aggiornare, valore out potenziometro*/
          lcd->video(25, "AUTOMATIC");
          lcd->clearDisplay();
          
        break;

        case PREALLARMTOOHIGH:
          servo->setPosition(setAngle(25)); /*da aggiornare, valore out potenziometro*/
          lcd->video(25, "AUTOMATIC");
          lcd->clearDisplay();

        break;

        case ALLARMTOOHIGH:
          servo->setPosition(setAngle(50)); /*da aggiornare, valore out potenziometro*/
          lcd->video(50, "AUTOMATIC");
          lcd->clearDisplay();

        break;

        case ALLARMTOOHIGHCRITIC:
          servo->setPosition(setAngle(100)); /*da aggiornare, valore out potenziometro*/
          lcd->video(100, "AUTOMATIC");
          lcd->clearDisplay();
        break;

        case ALLARMTOOLOW:
          servo->setPosition(setAngle(0)); /*da aggiornare, valore out potenziometro*/
          lcd->video(0, "AUTOMATIC");
          lcd->clearDisplay();
        break;

      }
    break;

    case MANUAL:
      int val = map(potentiometer->getValue(), 0, 1023, 0, 100);
      servo->setPosition(setAngle(val)); /*da aggiornare, valore out potenziometro*/
      lcd->video(val, "MANUAL");
    break;
  }

  
}

int setAngle(int percentage) {
    return percentage*180/100;
  }