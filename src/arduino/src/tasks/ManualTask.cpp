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
  int potValue = 0;  // Sostituire con la lettura del potenziometro

  // Adatta il valore del potenziometro alla posizione del servo (valore tra 0 e 180)
  int servoPosition = map(potValue, 0, maxPotValue, 0, 180);

  // Muovi il servo alla posizione calcolata
  servo->move(servoPosition);
}
