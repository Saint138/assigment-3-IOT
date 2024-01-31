#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../model/WaterController.h"
#include "../devices/Potentiometer.h"

class ValveTask: public Task {
public:
  ValveTask(ServoMotor* servoMotor, WaterController* waterController, Potentiometer* potentiometer, LCD* lcd);
  void init(int period);
  void tick();

private:
  WaterController* waterController;
  ServoMotor* servo;
  enum { AUTO, MANUAL} valvestate; 
  int setAngle(int percentage);
  Potentiometer* potentiometer;
  LCD* lcd;
};

#endif