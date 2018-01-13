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
const float JOYDELAY = 3000;
const int JOYSTICKTHRESH = 1000;
const int JOYMIDVALUE = 510;
float joystickCounter = JOYDELAY;

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
  if (joystickCounter < JOYDELAY) {
    //processJoystick();
    joystickCounter++;
  }
  
}

void displayJoyData(int angle) {
  
  if (angle > 45) {
      if (angle < 135) {
        Serial.println("Right");
      } else if (angle < 225) {
        Serial.println("Down");
      } else if (angle < 315) {
        Serial.println("Left");
      } else {
        Serial.println("Up");
      } 
    } else {
    
      Serial.println("Up");
    }

}

void processJoystick() {
  float x = analogRead(pinJoyX) - JOYMIDVALUE;
  float y = analogRead(pinJoyY) - JOYMIDVALUE;

  float norm = sqrt(sq(x)+sq(y));
  //Serial.println(norm);
  if (norm > 500 && joystickCounter == JOYDELAY) {
    float angle = atan(y/x)*360/(2*M_PI);
    if (x<0) {
      angle += 180;
    } else if (y<0 && x>0) {
      angle += 360;
    }
    joystickCounter = 0;
    displayJoyData(angle);
  }
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
