#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../model/WaterController.h"

class StateTask: public Task {
  private:
    WaterController* waterController;
  public:
    void tick();
    void init(int period);
    StateTask(WaterController* waterController);
};



#endif
