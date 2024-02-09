#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../model/WaterController.h"

class ValveTask: public Task {
public:
  ValveTask(WaterController* waterController);
  void init(int period);
  void tick();

private:
  WaterController* waterController;
  enum State {AUTO, MANUAL, DASHBOARD} valvestate;
  int setAngle(int percentage) {
      return percentage * 180 / 100;
  }
};

#endif