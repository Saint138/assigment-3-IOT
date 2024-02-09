#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../model/WaterController.h"
#include "../devices/Potentiometer.h"

int valveOpening;

class ValveTask: public Task {
public:
  ValveTask(ServoMotor* servoMotor, WaterController* waterController, Potentiometer* potentiometer, LCD* lcd);
  void init(int period);
  void tick();

private:
  WaterController* waterController;
  ServoMotor* servo;
  Potentiometer* potentiometer;
  LCD* lcd;
  enum {AUTO, MANUAL, DASHBOARD} valvestate; 
  int setAngle(int percentage);
};

#endif