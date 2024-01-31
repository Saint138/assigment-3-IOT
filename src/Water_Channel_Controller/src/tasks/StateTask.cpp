#include "StateTask.h"

StateTask::StateTask(WaterController* waterController) {
  this->waterController = waterController;
  automatic = true;
}

void StateTask::tick() {
    if(waterController->isButtonClicked()){
        if(automatic){
            automatic = false;
            waterController->LCDwrite("Manual");
        }else{
            automatic = true;
            waterController->LCDwrite("Automatic");
        }
    }
}