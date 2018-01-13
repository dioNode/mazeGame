#include <math.h>
#define _USE_MATH_DEFINES

// Analog input
int pinX = 1;
int pinY = 2;
int pinZ = 3;
int pinJoyX = 4;
int pinJoyY = 5;

// Digital input
int resetPin = 4;

// Joystick variables
int joyDirection = 0;   // 0=stop, 1=up, 2=down, 3=left, 4=right
//String[5] joyDirectionString = {"Stop", "Up", "Down", "Left", "Right"};
const int JOYSTICKTHRESH = 1000;
const int JOYMIDVALUE = 510;

// Accelerometer variables
int baseX = 0;
int baseY = 0;
int baseZ = 0;

void setup() {
  Serial.begin(9600);
  pinMode(resetPin, INPUT);
}

void printData(int x, int y, int z, String motion, String indentor, String newLine) {
  Serial.print(x);
  Serial.print(indentor);
  Serial.print(y);
  Serial.print(indentor);
  Serial.print(z);
  Serial.print(indentor);
  Serial.print(motion);
  Serial.println(newLine);
  delay(50);
}

void loop() {
  while (Serial.available() == 0);

  //processAccelerometer();
  processJoystick();
  
}

void processJoystick() {
  float x = analogRead(pinJoyX) - JOYMIDVALUE;
  float y = analogRead(pinJoyY) - JOYMIDVALUE;

  float norm = sqrt(sq(x)+sq(y));
  //Serial.println(norm);
  if (norm > 500) {
    float angle = atan(y/x)*360/(2*M_PI);
    
    Serial.print("Angle: ");
    Serial.println(angle);
  }
  
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
  //displayJoyData();
}

void displayJoyData() {
  
  

}

void processAccelerometer() {
  int x = analogRead(pinX);
  int y = analogRead(pinY);
  int z = analogRead(pinZ);
  int reset = digitalRead(resetPin);
  if (reset == HIGH) {
    baseX = x;
    baseY = y;
    baseZ = z;
  }
  int adjustedX = x-baseX;
  int adjustedY = y-baseY;
  int adjustedZ = z-baseZ;

  String status;
  float norm = sqrt(sq(float(adjustedX)) + sq(float(adjustedY)) + sq(float(adjustedZ)));
  
  if (norm < 100) {
    status = "No motion";
  } else {
    status = "Swing";
  }

  if (adjustedY > 120) {
    status = "Swipe right";
  } else if (adjustedY < -120) {
    status = "Swipe left";
  }
  
  printData(adjustedX, adjustedY, adjustedZ, status, "\t","\n");
}

