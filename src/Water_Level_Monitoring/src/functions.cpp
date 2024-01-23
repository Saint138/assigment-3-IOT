#include "functions.h"

#define ECHO_PIN 10
#define TRIG_PIN 11
#define MAXTIME 10000

void functions::waterDetectionTask(void* parameter) {
  Sonar* sonar = new Sonar(TRIG_PIN, ECHO_PIN, MAXTIME);


}