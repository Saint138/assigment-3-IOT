#include "StateTask.h"

bool automatic = true;
bool dashboard = false;

StateTask::StateTask(WaterController* waterController) {
  this->waterController = waterController;
}

void StateTask::init(int period) {
    Task::init(period);
}

void StateTask::tick() {
    if(waterController->isButtonClicked()){
        if(automatic){
            automatic = false;
        } else {
            automatic = true;
        }
        dashboard = false;
    }
}