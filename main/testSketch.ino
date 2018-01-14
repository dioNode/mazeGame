#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=300;  // Delay between Frames
bool lateral; // tracks if the maze entrances are in line w/ byte rows or perpendicular

void setup() {
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,10);  // Set intensity levels
  lc.setIntensity(1,10);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
}

byte mazeWalls[] {
  0,
  0xFF,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  0xFF
};

int entranceWalls[2] = {0,0};

void insertDoor(int wall, int space) {
  lateral = wall%2==1;
  switch (wall) {
    case 0:
      mazeWalls[1] = mazeWalls[1] ^ (1 << space);
      entranceWalls[0] = 0;
      break;
    case 1:
      mazeWalls[space] = mazeWalls[space] & B11111110; 
      entranceWalls[0] = 1;
      break;
    case 2:
      mazeWalls[7] = mazeWalls[7] ^ (1 << space);
      entranceWalls[0] = 2;
      break;
    case 3:
      mazeWalls[space] = mazeWalls[space] & B01111111;
      entranceWalls[0] = 3;
      break;
    }
  }
/*
void newStartGen() {
  int newWall = random(0, 2);
  int a = random(1, 7); // 1 - 6 randint
  byte newStart = ~(1 << a);

  insertDoor(newWall, a);  
}

void newExitGen() {
  int newWall = random(2, 4);
  int a = random(1, 7);
  byte newExit = ~(1<<a);
  
  insertDoor(newWall, a);
}
*/

// Generates the entrance and exit on the rows in line with the bytes of the maze
// Transposition happens later, if necessary
void genDoors() {
  int startSpace = random(1,7);
  int endSpace = random(1,7);
  insertDoor(0, startSpace);
  insertDoor(2, endSpace);
  }

void mazeReset() {
  mazeWalls[0] = 0;
  mazeWalls[1] = B11111111;
  for (int i = 2; i < 7; i++) {
    mazeWalls[i] = B10000001;
  }
  mazeWalls[7] = B11111111;
}

void rotateMaze() {
  byte newMaze[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int newRow = 0; newRow < 8; newRow++) {
    for (int newCol = 0; newCol < 8; newCol++) {
      newMaze[newRow] |= ((mazeWalls[7-newCol]& (1<<newRow) )>>newRow<<newCol);
      }
    }

  for (int row = 0; row < 8; row++) {
    mazeWalls[row] = newMaze[row];
    }
  }

void playFrame() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, mazeWalls[i]);
  }
  //mazeGen();
  
  mazeReset();
  genDoors();
  genInlineMaze();

  // Rotate and/or flip maze
  int manu = random(0,4);
  while (manu > 0) {
    rotateMaze();
    manu -= 1;
    }
  
  /*
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
  mazeGen();*/
  
  
}

void genInlineMaze() {
  for (int row = 3; row < 6; row +=2) {
    mazeWalls[row] = ~(1<<random(1,7));
    }
  }

//void mazeGen() {
//  // hardcoded maze
//  /*mazeWalls[0] = B11011111;
//  mazeWalls[1] = B10000101;
//  mazeWalls[2] = B10010001;
//  mazeWalls[3] = B10100101;
//  mazeWalls[4] = B11001011;
//  mazeWalls[5] = B01011101;
//  mazeWalls[6] = B01000101;
//  mazeWalls[7] = B11110111;*/
//  
//  int guess;
//  for (int i = 1; i < 7; i++) {
//    for (int j = 1; j < 7; j++) {
//      guess = random(0,2);
//      if (guess != 0) {
//        mazeWalls[i] = mazeWalls[i] | (1 << j);  
//      }
//    }
//  }
//}

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
  delay(delayTime*10);
}
