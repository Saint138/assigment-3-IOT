#ifndef __AUTOMATICTASK__
#define __AUTOMATICTASK__

#include "Task.h"
#include "../devices/ServoMotor.h"
#include "../devices/SonarSensor.h"

class AutomaticTask : public Task {
public:
  AutomaticTask(ServoMotor* servoMotor, SonarSensor* sonarSensor);
  void init(int period);
  void tick();

private:
  ServoMotor* servo;
  SonarSensor* sonar;
};

#endif
