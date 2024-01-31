#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

#include "model/WaterController.h" 
#include "config.h"

class SerialCommunication {
public:
    SerialCommunication(WaterController* pcw);
    void init();
    void update();
    bool isMsgAvailable();
    String getMsg();
    

private:
    static WaterController* waterController;
    String stateAsString(State currentState);
};

#endif