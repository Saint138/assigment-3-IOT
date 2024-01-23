#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
}


int Potentiometer::getShaftValue() {
  int nuovo = analogRead(pin);
  //Serial.println(nuovo);
  if (nuovo != last) {
    last = nuovo;
  }
  return last;
}
