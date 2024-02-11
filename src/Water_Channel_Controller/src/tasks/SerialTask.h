#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "Task.h"
#include "./model/WaterController.h"

class SerialTask: public Task {
public:
  SerialTask(WaterController* waterController);
  void init(int period);
  void tick();

private:
  WaterController* waterController;
  String lastMsg;
  bool isMsgAvailable();
  String stateAsString(State currentState);
  String getMsg();
};

#endif
