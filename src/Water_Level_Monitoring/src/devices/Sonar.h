#ifndef __SONAR__
#define __SONAR__

#include "proximitySensor.h"

#define NO_OBJ_DETECTED -1

class Sonar: public ProximitySensor {

public:  
  Sonar(int echoPin, int trigPin, long timeOut);
  float getDistance();
  void setTemperature(float temp);  
  int toInt();

private:
    const float vs = 331.5 + 0.6*20;
    float getSoundSpeed();
    
    float temperature;    
    int echoPin, trigPin;
    long timeOut;
};

#endif 