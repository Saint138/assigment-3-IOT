#include "./devices/led.h"
#include "./devices/sonar.h"
#include <Arduino.h>

#define ECHO_PIN 10
#define TRIG_PIN 11
#define MAXTIME 10000

class functions {
    public:
        static void waterDetectionTask(void* parameter);
        static float getWaterLevel();
        static float waterLevel;
};