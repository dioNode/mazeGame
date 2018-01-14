#include <math.h>
#define _USE_MATH_DEFINES

// Analog input
int pinX = 1;
int pinY = 2;
int pinZ = 3;
int pinJoyX = 4;
int pinJoyY = 5;

// Joystick variables
const float JOYDELAY = 2000;
const int JOYSTICKTHRESH = 1000;
const int JOYMIDVALUE = 510;
float joystickCounter = JOYDELAY;
int joystickStatus = 0;

// Digital input
int resetPin = 4;

// Accelerometer variables
String accelerometerStatus = "";
int baseX = 0;
int baseY = 0;
int baseZ = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting program...");
  pinMode(resetPin, INPUT);
}

void loop() {
  accelerometerStatus = processAccelerometer();
  processJoystick();
  if (joystickCounter < JOYDELAY) {
    joystickCounter++;
  }
}
