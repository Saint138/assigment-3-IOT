#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(ServoMotor* servoMotor){
  this->servo = servoMotor;
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
    break;

    case MANUAL:
      servo->setPosition(0); /*da aggiornare, valore out potenziometro*/
    break;
  }
}