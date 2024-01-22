#include "AutomaticTask.h"

AutomaticTask::AutomaticTask(ServoMotor* servoMotor, SonarSensor* sonarSensor) {
  this->servo = servoMotor;
  this->sonar = sonarSensor;
}

void AutomaticTask::init(int period) {
  Task::init(period);
}

void AutomaticTask::tick() {
  // Leggi il valore dal sensore sonar (da implementare nella tua applicazione)
  int sonarValue = 0;  // Sostituire con la lettura del sensore sonar

  // Adatta il valore del sonar alla posizione del servo (valore tra 0 e 180)
  int servoPosition = map(sonarValue, 0, maxSonarValue, 0, 180);

  // Muovi il servo alla posizione calcolata
  servo->move(servoPosition);
}
