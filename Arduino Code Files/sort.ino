// Function to print a 2D array
const int motorTicks = 2043;
int array1[5][2]; // Define array1 as a global variable
int array2[5][2]; // Define array2 as a global variable
int array3[5][2]; // Define array3 as a global variable
int array4[5][2]; // Define array4 as a global variable

void printArray(int arr[][2], int length) {
  for (int i = 0; i < length; i++) {
    Serial.print("[");
    Serial.print(arr[i][0]);
    Serial.print(",");
    Serial.print(arr[i][1]);
    Serial.println("]");
  }
}

int target(int x, int y,int arm[][2],int call) {
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

void sortArrayAscending(int arr[][2], int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = 0; j < length - i - 1; j++) {
      if (arr[j][0] > arr[j + 1][0]) {
        int tempX = arr[j][0];
        int tempY = arr[j][1];
        arr[j][0] = arr[j + 1][0];
        arr[j][1] = arr[j + 1][1];
        arr[j + 1][0] = tempX;
        arr[j + 1][1] = tempY;
      }
    }
  }
}

void sortArrays(int mainArray[][2], int length) {
  int array1[length][2];
  int array2[length][2];
  int array3[length][2];
  int array4[length][2];

  int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

  for (int i = 0; i < length; i++) {
    int X = mainArray[i][0];
    int Y = mainArray[i][1];

    // Conditions for sorting into different arrays
    if (X >= 0 && X <30) {
      array1[count1][0] = X-15;
      array1[count1][1] = Y-20;
      count1++;
    } else if (X >= 30 && X <60) {
      array2[count2][0] = X-45;
      array2[count2][1] = Y-20;
      count2++;
    } else if (X >= 60 && X <90) {
      array3[count3][0] = X-75;
      array3[count3][1] = Y-20;
      count3++;
    } else if (X >= 90 && X <120) {
      array4[count4][0] = X-105;
      array4[count4][1] = Y-20;
      count4++;
    }
  }

  // Print the sorted arrays (optional)
  /*Serial.println("Array 1:");
  printArray(array1, count1);
  Serial.println("Array 2:");
  printArray(array2, count2);
  Serial.println("Array 3:");
  printArray(array3, count3);
  Serial.println("Array 4:");
  printArray(array4, count4);*/

  // Call target function on each element in the sorted arrays
  for (int i = 0; i < count1; i++) {
    target(array1[i][0], array1[i][1], array1, i);
  }
  for (int i = 0; i < count2; i++) {
    target(array2[i][0], array2[i][1], array2, i);
  }
  for (int i = 0; i < count3; i++) {
    target(array3[i][0], array3[i][1], array3, i);
  }
  for (int i = 0; i < count4; i++) {
    target(array4[i][0], array4[i][1], array4, i);
  }
  sortArrayAscending(array1, count1);
  sortArrayAscending(array2, count2);
  sortArrayAscending(array3, count3);
  sortArrayAscending(array4, count4);
  Serial.println("Array 1 sorted targets:");
  printArray(array1, count1); 
  Serial.println("Array 2 sorted targets:");
  printArray(array2, count2);
  Serial.println("Array 3 sorted targets:");
  printArray(array3, count3);
  Serial.println("Array 4 sorted targets:");
  printArray(array4, count4);
}



void setup() {
  Serial.begin(9600);
  int mainArray[][2] = {{22,2},{56,30},{97,22},{13,12},{41,11},{116,39},{76,23},{17,10},{61,4},{15,47}};
  int length = sizeof(mainArray) / sizeof(mainArray[0]);
  sortArrays(mainArray, length);
}

void loop() {
  // Your main loop code (if any)
}
