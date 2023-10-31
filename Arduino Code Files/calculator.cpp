#include "calculator.h"
const int motorTicks = 2043;

//function takes in coordiates, an arm array and produces a
int target(int x, int y,int arm[5][2],int call) {
  int angleOffset;
  int xTarget;
  int yTarget;
  int mode = 0;
  float rotDist;
  float linDist;
  
  //determine where this coord falls
  if (x < 0 && y > 0) {// Region 1
    xTarget=x;
    yTarget=y;
    angleOffset =0; 
    mode = 1;
  } else if (x > 0 && y > 0) {// Region 2
    xTarget=y;
    yTarget=x;
    angleOffset =motorTicks/4; 
    mode = 1;
  } else if (x > 0 && y < 0) {// Region 3
    xTarget=x;
    yTarget=y;
    angleOffset =motorTicks/2; 
    mode = 1;
  } else if (x < 0 && y < 0) {// Region 4
    xTarget=y;
    yTarget=x;
    angleOffset =motorTicks*3/4; 
    mode = 1;
  } else if (x == 0 && y > 0) {// Positive Y region
    rotDist =motorTicks/4; 
    linDist=((y-4.2)/9.786061)*motorTicks;
  } else if (x == 0 && y < 0) {// Negative Y region
    rotDist =motorTicks*3/4; 
    linDist=((abs(y)-4.2)/9.786061)*motorTicks;
  } else if (y == 0 && x > 0) {// Positive X region
    rotDist =motorTicks/2; 
    linDist=((x-4.2)/9.786061)*motorTicks;
  } else if (y == 0 && x < 0) {// Negative X region
    rotDist =0; 
    linDist=((abs(x)-4.2)/9.786061)*motorTicks;
  } else { // Origin NOTE: cannot target this region in my prototype
    return 0; 
  }

  if (mode==1){
    rotDist = (((atan(abs(yTarget/xTarget)))/6.28319)*motorTicks)+angleOffset;
    linDist = (((sqrt(sq(xTarget)+sq(yTarget)))-4.2)/9.786061)*motorTicks;
  }
  
  arm[call][0]=rotDist;
  arm[call][1]=linDist;
  
  return arm[call];
}

//used to sort arrays into ascending order of rotational movement
void bubbleSort(int arr[][2], int length) {
  for (int i = 0; i < length-1; i++) {
    for (int j = 0; j < length-i-1; j++) {
      if (arr[j][1] > arr[j+1][1]) {
        // Swap the elements
        int temp0 = arr[j][0];
        int temp1 = arr[j][1];
        arr[j][0] = arr[j+1][0];
        arr[j][1] = arr[j+1][1];
        arr[j+1][0] = temp0;
        arr[j+1][1] = temp1;
      }
    }
  }
}
