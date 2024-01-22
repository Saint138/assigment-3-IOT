#include "ButtonStateTask.h"

ButtonStateTask::ButtonStateTask(ServoMotor* servoMotor) : automaticTask(servoMotor), manualTask(servoMotor) {
  this->servo = servoMotor;
}

void ButtonStateTask::init(int period) {
  Task::init(period);
  buttonState = AUTOMATIC;
  lastButtonState = false;
}

void ButtonStateTask::tick() {
  // Simula il rilevamento del pulsante (da implementare nella tua applicazione)
  bool buttonPressed = false;  // Sostituire con la lettura del pulsante

  if (buttonPressed && !lastButtonState) {
    // Cambia lo stato del pulsante
    buttonState = (buttonState == AUTOMATIC) ? MANUAL : AUTOMATIC;
  }

  lastButtonState = buttonPressed;

  switch (buttonState) {
    case AUTOMATIC:
      automaticTask.tick();  // Avvia AutomaticTask se si è nello stato AUTOMATIC
      break;

    case MANUAL:
      manualTask.tick();  // Avvia ManualTask se si è nello stato MANUAL
      break;
  }
}
