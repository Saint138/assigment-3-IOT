#include <Arduino.h>
#include <tasks/Task.h>
#include "kernel/Scheduler.h"
#include "kernel/SerialCommunication.h"
#include "tasks/StateTask.h"
#include "tasks/ValveTask.h"
#include "tasks/SerialTask.h"
#include "model/WaterController.h"

Scheduler sched;
LCD* lcd;
Button* button;
Potentiometer* potentiometer;
ServoMotor* servoMotor;
WaterController* waterController;

void setup() {
  sched.init(200);

  Serial.begin(9600);

  servoMotor = new ServoMotorImpl(SERVO_PIN);
  lcd = new LCD();
  button = new ButtonImpl(BUT_PIN);
  potentiometer = new Potentiometer(POT_PIN);
  waterController = new WaterController(button, servoMotor, lcd);

  Task* valveTask = new ValveTask(servoMotor, waterController, potentiometer, lcd);
  Task* stateTask = new StateTask(waterController);
  Task* serialTask = new SerialTask(waterController);

  valveTask->init(200);
  stateTask->init(200);
  serialTask->init(200);

  sched.addTask(valveTask);
  sched.addTask(stateTask);
  sched.addTask(serialTask);
}

void loop() {
  sched.schedule();
}
