#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../devices/ButtonImpl.h"
#include <model/SmartRiver.h>

bool automatic;

class StateTask: public Task {
public:
  
  void tick();
  StateTask(SmartRiver *smartRiver);

private:
SmartRiver *smartRiver;

};



#endif
