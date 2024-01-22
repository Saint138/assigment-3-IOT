#ifndef __AUTOMATICTASK__
#define __AUTOMATICTASK__

#include "Task.h"
#include "../devices/ServoMotor.h"
#include "../devices/Sonar.h"

class AutomaticTask : public Task {
public:
  AutomaticTask(ServoMotor* servoMotor, Sonar* Sonar);
  void init(int period);
  void tick();

private:
  ServoMotor* servo;
  Sonar* sonar;
};

#endif
