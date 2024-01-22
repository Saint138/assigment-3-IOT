#include "ManualTask.h"

ManualTask::ManualTask(ServoMotor* servoMotor, Potentiometer* potentiometer) {
  this->servo = servoMotor;
  this->potentiometer = potentiometer;
}

void ManualTask::init(int period) {
  Task::init(period);
}

void ManualTask::tick() {
  // Leggi il valore dal potenziometro (da implementare nella tua applicazione)
  int potValue = potentiometer->getShaftValue();  // Sostituire con la lettura del potenziometro

  // Muovi il servo alla posizione calcolata
  servo->setPosition(potValue);
}
