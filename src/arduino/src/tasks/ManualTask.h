#ifndef __MANUALTASK__
#define __MANUALTASK__

#include "Task.h"
#include "../devices/ServoMotor.h"
#include "../devices/Potentiometer.h"

class ManualTask : public Task {
public:
  ManualTask(ServoMotor* servoMotor, Potentiometer* potentiometer);
  void init(int period);
  void tick();

private:
  ServoMotor* servo;
  Potentiometer* potentiometer;
};

#endif
