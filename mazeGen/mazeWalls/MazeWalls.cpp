#include "MazeWalls.h"

void MazeWalls::MazeWalls() {
  lc=LedControl(12,11,10,1);  // Pins: DIN,CLK,CS, # of Display connected
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,10);  // Set intensity levels
  lc.setIntensity(1,10);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
}


void MazeWalls::insertDoor(int wall, int space) {
  switch (wall) {
    case 0:
      mazeWalls[1] = mazeWalls[1] ^ (1 << space);
      break;
    case 1:
      mazeWalls[space] = mazeWalls[space] & B11111110; 
      break;
    case 2:
      mazeWalls[7] = mazeWalls[7] ^ (1 << space);
      break;
    case 3:
      mazeWalls[space] = mazeWalls[space] & B01111111;
      break;
    }
  }

// Generates the entrance and exit on the rows in line with the bytes of the maze
// Transposition happens later, if necessary
void MazeWalls::genDoors() {
  int startSpace = random(1,7);
  int endSpace = random(1,7);
  insertDoor(0, startSpace);
  insertDoor(2, endSpace);
  }

void MazeWalls::mazeReset() {
  mazeWalls[0] = 0;
  mazeWalls[1] = B11111111;
  for (int i = 2; i < 7; i++) {
    mazeWalls[i] = B10000001;
  }
  mazeWalls[7] = B11111111;
}

void MazeWalls::rotateMaze() {
  char newMaze[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int newRow = 0; newRow < 8; newRow++) {
    for (int newCol = 0; newCol < 8; newCol++) {
      newMaze[newRow] |= ((mazeWalls[7-newCol]& (1<<newRow) )>>newRow<<newCol);
      }
    }

  for (int row = 0; row < 8; row++) {
    mazeWalls[row] = newMaze[row];
    }
  }

void MazeWalls::makeFrame() {
  int temp[8] = DEFAULTMAZE;
  for (row = 0; row< 8; row++) {
    mazeWalls[row] = temp[row];
  }
  
  mazeReset();
  genDoors();
  genInlineMaze();

  // Rotate and/or flip maze
  int manu = random(0,4);
  while (manu > 0) {
    rotateMaze();
    manu -= 1;
    }

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, mazeWalls[i]);
    }
}

void MazeWalls::genInlineMaze() {
  for (int row = 3; row < 6; row +=2) {
    mazeWalls[row] = ~(1<<random(1,7));
    }
  }

bool MazeWalls::isWallAt(int row, int col) {
  return mazeWalls[row]&(1<<col) != 0;
}