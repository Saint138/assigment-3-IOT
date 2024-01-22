#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../devices/ServoMotor.h"


class ValveTask: public Task {
public:
  ValveTask(ServoMotor* servoMotor);
  void init(int period);
  void tick();

private:
  ServoMotor* servo;
  enum { AUTO, MANUAL} valvestate;
};

#endif