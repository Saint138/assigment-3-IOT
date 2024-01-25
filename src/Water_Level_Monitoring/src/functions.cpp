#include "functions.h"

// Inizializzazione della variabile statica
float functions::waterLevel = 0.0;

void functions::waterDetectionTask(void* parameter) {
    Sonar* sonar = new Sonar(TRIG_PIN, ECHO_PIN, MAXTIME);
    for (;;) {

        float currentWaterLevel = sonar->getDistance();

        waterLevel = currentWaterLevel;
    }
}

float functions::getWaterLevel() {
    return waterLevel;
}
