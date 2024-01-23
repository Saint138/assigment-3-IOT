#ifndef __SERIAL_COMMUNICATION__
#define __SERIAL_COMMUNICATION__

#include "model/SmartRiver.h" 
#include "config.h"

class SerialCommunication {
public:
    SerialCommunication(SmartRiver* pcw);
    void init();
    void update();
    bool isMsgAvailable();
    String getMsg();
    

private:
    static SmartRiver* pSmartRiver;
    String stateAsString(State currentState);
};

#endif