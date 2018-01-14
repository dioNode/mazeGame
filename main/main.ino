#include <math.h>
#define _USE_MATH_DEFINES

// Maze temp

// Sample maze to load
byte sampleMaze[] {
  B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};

// Sample maze to modify
byte outputMaze[] {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};


// Analog input
int pinX = 1;
int pinY = 2;
int pinZ = 3;
int pinJoyX = 4;
int pinJoyY = 5;

// Joystick variables
const float JOYDELAY = 3000;
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
  setupMaze();
}



void loop() {
  //accelerometerStatus = processAccelerometer();
  processJoystick();
  if (joystickCounter < JOYDELAY) {
    joystickCounter++;
  }
}
