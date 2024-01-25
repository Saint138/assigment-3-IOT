#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../devices/ServoMotor.h"
#include "../model/SmartRiver.h"
#include "../devices/Potentiometer.h"
#include "../devices/LCD.h"


class ValveTask: public Task {
public:
  ValveTask(ServoMotor* servoMotor, SmartRiver* smartRiver, Potentiometer* potentiometer, LCD* lcd);
  void init(int period);
  void tick();

private:
  SmartRiver* smartRiver;
  ServoMotor* servo;
  enum { AUTO, MANUAL} valvestate; 
  int setAngle(int percentage);
  Potentiometer* potentiometer;
  LCD* lcd;
};

#endif