#include <AccelStepper.h>
#include "calculator.h"

#define FULLSTEP 4

int arm_1[5][2]={{0,0},{0,0},{0,0},{0,0},{0,0}};//arm array initialization

// Creates two instances
AccelStepper linear1(FULLSTEP, 4, 3, 5, 7);
AccelStepper rotational1(FULLSTEP, 8,10,9,11);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rotational1.setMaxSpeed(2000.0);
  rotational1.setAcceleration(250.0);
  linear1.setMaxSpeed(500.0);
  linear1.setAcceleration(500.0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int xTarget = 0;
  int yTarget = -24;
  int* result = target(xTarget, yTarget, arm_1, 0);
  /*Serial.print("arm array: ");
  Serial.print(result[0]);
  Serial.print(", ");
  Serial.println(result[1]);*/
  Serial.println("arm_1 array:");
  for (int i = 0; i < 5; i++) {
    Serial.print(arm_1[i][0]);
    Serial.print(", ");
    Serial.println(arm_1[i][1]);
  }
  delay(2000);
}
