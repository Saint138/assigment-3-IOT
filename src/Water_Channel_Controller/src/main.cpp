#include <Arduino.h>
#include <tasks/Task.h>
#include "kernel/Scheduler.h"
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
  sched.init(100);

  Serial.begin(9600);

  servoMotor = new ServoMotorImpl(SERVO_PIN);
  lcd = new LCD();
  button = new ButtonImpl(BUT_PIN);
  potentiometer = new Potentiometer(POT_PIN);
  waterController = new WaterController(button, servoMotor, lcd);

  Task* valveTask = new ValveTask(waterController, potentiometer);
  Task* stateTask = new StateTask(waterController);
  Task* serialTask = new SerialTask(waterController);

  stateTask->init(800);
  valveTask->init(1000);
  serialTask->init(2000);

  sched.addTask(serialTask);
  sched.addTask(stateTask);
  sched.addTask(valveTask);
}

void loop() {
  sched.schedule();
}
