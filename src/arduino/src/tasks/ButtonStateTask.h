#ifndef __BUTTONSTATETASK__
#define __BUTTONSTATETASK__

#include "Task.h"
#include "AutomaticTask.h"
#include "ManualTask.h"

class ButtonStateTask : public Task {
public:
  ButtonStateTask(ServoMotor* servoMotor);
  void init(int period);
  void tick();

private:
  ServoMotor* servo;
  Sonar* sonarSensor;
  Potentiometer* potentiometer;
  enum { AUTOMATIC, MANUAL } buttonState;
  bool lastButtonState;
  AutomaticTask automaticTask;
  ManualTask manualTask;
};

#endif
