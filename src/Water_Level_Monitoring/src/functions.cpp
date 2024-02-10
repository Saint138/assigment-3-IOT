#include "functions.h"

// Inizializzazione della variabile statica
int functions::waterLevel = 0;

void functions::waterDetectionTask(void* parameter) {
    Sonar* sonar = new Sonar(TRIG_PIN, ECHO_PIN, MAXTIME);
    for (;;) {

      int currentWaterLevel = sonar->toInt();
      
        waterLevel = currentWaterLevel;
        }
}

int functions::getWaterLevel() {
    return waterLevel;
}
