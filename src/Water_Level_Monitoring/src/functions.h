#include "./devices/led.h"
#include "./devices/sonar.h"
#include <Arduino.h>

#define ECHO_PIN 5
#define TRIG_PIN 6
#define MAXTIME 10000

class functions {
    public:
        static void waterDetectionTask(void* parameter);
        static int getWaterLevel();
        static int waterLevel;
};