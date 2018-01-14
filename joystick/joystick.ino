#include <math.h>
#define _USE_MATH_DEFINES

// Analog input
int pinJoyX = 4;
int pinJoyY = 5;


// Joystick variables
const float JOYDELAY = 3000;
const int JOYSTICKTHRESH = 1000;
const int JOYMIDVALUE = 510;
float joystickCounter = JOYDELAY;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0);
  
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

