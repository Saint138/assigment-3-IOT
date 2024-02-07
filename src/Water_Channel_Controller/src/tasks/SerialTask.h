#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "Task.h"
#include <ArduinoJson.h>
#include "./model/WaterController.h"

extern int valveOpening;
extern bool automatic;
extern bool dashboard;

class SerialTask: public Task {
public:
  SerialTask(WaterController* waterController);
  void init(int period);
  void tick();

private:
  WaterController* waterController;
  String stateAsString(State currentState);
  bool isMsgAvailable();
  String getMsg();
};

#endif
