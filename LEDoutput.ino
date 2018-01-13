#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=300;  // Delay between Frames

void setup() {
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,10);  // Set intensity levels
  lc.setIntensity(1,10);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
}

byte mazeWalls[] {
  B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};

int entranceWalls[2] = {0,0};

void newStartGen() {
  int newWall = random(0, 3);
  int a = random(1, 6);
  byte newStart = 1 << a;
  newStart = !newStart;
  
  if (newWall == 0) {
    mazeWalls[0] = mazeWalls[0] ^ (1 << a);
    entranceWalls[0] = 0;
  } else if (newWall == 1) {
    mazeWalls[a] = mazeWalls[a] & B11111110; 
    entranceWalls[0] = 1;
  } else if (newWall == 2) {
    mazeWalls[7] = mazeWalls[7] ^ (1 << a);
    entranceWalls[0] = 2;
  } else if ((newWall == 3) || (newWall == 4)){
    mazeWalls[a] = mazeWalls[a] & B01111111;
    entranceWalls[0] = 3;
  }
   
}

void newExitGen() {
  int newWall = random(0, 4);
  int a = random(1, 6);
  byte newExit = 1 << a;
  newExit = !newExit;
  if (newWall == 0) {
    mazeWalls[0] = mazeWalls[0] ^ (1 << a);
    entranceWalls[1] = 0;
  } else if (newWall == 1) {
    mazeWalls[a] = mazeWalls[a] & B11111110; 
    entranceWalls[1] = 1;
  } else if (newWall == 2) {
    mazeWalls[7] = mazeWalls[7] ^ (1 << a);
    entranceWalls[1] = 2;
  } else if ((newWall == 3) || (newWall == 4)){
    mazeWalls[a] = mazeWalls[a] & B01111111;
    entranceWalls[1] = 3;
  }
  
}

void mazeReset() {
  mazeWalls[0] = B11111111;
  for (int i = 1; i < 7; i++) {
    mazeWalls[i] = B10000001;
  }
  mazeWalls[7] = B11111111;
}
void playFrame() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, mazeWalls[i]);
  }
  //mazeGen();
  
  mazeReset();
  
  int valid = 0;
  while (!valid) {
    newStartGen();
    newExitGen();
    if (entranceWalls[0] == entranceWalls[1]) {
      valid = 0;
      mazeReset();
    } else {
      valid = 1;
    }
  }
  mazeGen();
  delay(delayTime*10);
  
}

void mazeGen() {
  // hardcoded maze
  /*mazeWalls[0] = B11011111;
  mazeWalls[1] = B10000101;
  mazeWalls[2] = B10010001;
  mazeWalls[3] = B10100101;
  mazeWalls[4] = B11001011;
  mazeWalls[5] = B01011101;
  mazeWalls[6] = B01000101;
  mazeWalls[7] = B11110111;*/
  
  int guess;
  for (int i = 1; i < 7; i++) {
    for (int j = 1; j < 7; j++) {
      guess = random(0,2);
      if (guess != 0) {
        mazeWalls[i] = mazeWalls[i] | (1 << j);  
      }
    }
  }
}

/*void pathSuperimpose() {
  if (entranceWalls[0] == 0) {
    for (int i = 7; i = 0; i--) {
      if ((mazeWalls[0] & (1 << i)) != 0) {
        int startCol =      
      }
    }
    
  }
}*/

void loop() {
  playFrame();
  /*
  byte state = B10000000;
  byte blankState = B00000000;
 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.setRow(0,i,state);
      delay(delayTime);
      //lc.setRow(0,i,blankState);
      //delay(delayTime);
      state = state >> 1;  
    }
    state = B10000000;
  }
  */
}
