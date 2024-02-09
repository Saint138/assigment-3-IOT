#include "StateTask.h"

StateTask::StateTask(WaterController* waterController) {
  this->waterController = waterController;
  automatic = true;
  dashboard = false;
}

void StateTask::tick() {
    if(waterController->isButtonClicked()){
        if(automatic){
            automatic = false;
        }else{
            automatic = true;
        }
        dashboard = false;
    }
}