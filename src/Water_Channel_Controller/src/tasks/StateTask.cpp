#include "StateTask.h"

StateTask::StateTask(SmartRiver *smartRiver) {
  this->smartRiver = smartRiver;
  automatic = true;
}

void StateTask::tick() {
    if(smartRiver->isButtonClicked()){
        if(automatic){
            automatic = false;
            smartRiver->LCDwrite("Manual");
        }else{
            automatic = true;
            smartRiver->LCDwrite("Automatic");
        }
    }
}