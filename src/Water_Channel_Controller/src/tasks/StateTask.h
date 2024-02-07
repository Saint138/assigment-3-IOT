#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../model/WaterController.h"

bool automatic;
bool dashboard;
extern int valveOpening;

class StateTask: public Task {
public:
  
  void tick();
  StateTask(WaterController* waterController);

private:
WaterController* waterController;

};



#endif
