#include "AutomaticTask.h"

AutomaticTask::AutomaticTask(ServoMotor* servoMotor, Sonar* sonarSensor) {
  this->servo = servoMotor;
  this->sonar = sonarSensor;
}

void AutomaticTask::init(int period) {
  Task::init(period);
}

void AutomaticTask::tick() {
  // Leggi il valore dal sensore sonar (da implementare nella tua applicazione)
  int sonarValue = 0;  // Sostituire con la lettura del sensore sonar

  // Muovi il servo alla posizione calcolata
  servo->setPosition(sonarValue);
}
