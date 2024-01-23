#include "./devices/led.h"
#include "./devices/sonar.h"
#include <Arduino.h>

class functions {
    public:
        static void waterDetectionTask(void* parameter);
};