#include "StateTask.h"

StateTask::StateTask(WaterController* waterController) {
  this->waterController = waterController;
}

void StateTask::init(int period) {
    Task::init(period);
}

void StateTask::tick() {
    if(waterController->isButtonClicked()){
        if(waterController->isAutomatic()){
            waterController->setAutomatic(false);
        } else {
            waterController->setAutomatic(true);
        }
        waterController->setDashboard(false);
    }
}