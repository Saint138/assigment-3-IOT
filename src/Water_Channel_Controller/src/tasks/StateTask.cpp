#include "StateTask.h"

StateTask::StateTask(SmartRiver *smartRiver) {
  this->smartRiver = smartRiver;
  automatic = true;
}

void SerialTask::tick() {
    if(isButtonClicked()){
        if(automatic){
            automatic = false;
            LCDwrite("Manual");
        }else{
            automatic = true;
            LCDwrite("Automatic");
        }
    }
}