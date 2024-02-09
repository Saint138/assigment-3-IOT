#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../model/WaterController.h"

bool automatic;
bool dashboard;

class StateTask: public Task {
  private:
    WaterController* waterController;
  public:
    void tick();
    StateTask(WaterController* waterController);
};



#endif
