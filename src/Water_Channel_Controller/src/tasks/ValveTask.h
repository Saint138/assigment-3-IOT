#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../model/WaterController.h"
#include "../devices/Potentiometer.h"

extern bool automatic;
extern bool dashboard;

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
  enum State {AUTO, MANUAL, DASHBOARD} valvestate;
  int setAngle(int percentage) {
      return percentage * 180 / 100;
  }
};

#endif