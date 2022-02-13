#include <Stepper.h>

const int stepsPerRevolution = 2038;
const int msPerStep = 30;
const int Start = 3;
const int Stop = 4;

unsigned long lastTime = 0;
unsigned long currentTime = 0;
int stepsTaken = 0;
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(180);
  pinMode(Start, INPUT_PULLUP);
  pinMode(Stop, INPUT_PULLUP);
}

void loop() {
  while(digitalRead(Start) == HIGH);
  lastTime = millis();
  while(digitalRead(Stop) == HIGH && stepsTaken < stepsPerRevolution)
  {
    currentTime = millis();
    if(currentTime - lastTime >= msPerStep)
    {
      myStepper.step(1);
      stepsTaken++;
      lastTime = currentTime;
    }
  }
  if(stepsTaken < stepsPerRevolution) myStepper.step(-stepsTaken);
  stepsTaken = 0;
}
