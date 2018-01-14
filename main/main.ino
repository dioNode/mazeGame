#include "LedControl.h"
#include "SSDTimer.h"

LedControl lc=LedControl(12,11,10,1);  // Pins: DIN,CLK,CS, # of Display connected
SSDTimer timer = SSDTimer();

unsigned long delayTime=300;  // Delay between Frames
unsigned long lastTick;
int pinJoyX = 19;
int pinJoyY = 18;

///////////////////////////////////////// JOYSTICK //////////////////////////////////////////
int displayJoyData(int angle) {
  
  if (angle > 45) {
      if (angle < 135) {
        // Right
        return 4;
      } else if (angle < 225) {
        // Down
        return 2;
      } else if (angle < 315) {
        // Left
        return 3;
      } else {
        // Up
        return 1;
      } 
    } else {
      // Up
      return 1;
    }
}

int processJoystick() {
  float x = analogRead(pinJoyX) - 512;
  float y = analogRead(pinJoyY) - 512;

  float norm = sqrt(sq(x)+sq(y));
  if (norm > 500) {
    float angle = atan(y/x)*360/(2*M_PI);
    if (x<0) {
      angle += 180;
    } else if (y<0 && x>0) {
      angle += 360;
    }
    return displayJoyData(angle);
  } else {
    return 0;
  }
}



///////////////////////////////////////// Player ENTITY ////////////////////////////////////

class SAMazeModel {

  public:
  
  /*
   * Describes a point that exists with a x and y.
   */
  struct SAPoint {
    int x;
    int y;
  };
  
  SAPoint playerPosition = {0,0};

  int mazeMatrix[8][8];  // Stores the maze representation

  void movePlayerUp() {
    if (wallAt(playerPosition.x, playerPosition.y-1)) {
      // Wall at this location
    } else {
      // No wall at this location
      playerPosition.y--;
    }
  }

  void movePlayer() {
    int dir = processJoystick();
    switch (dir) {
      case 1:
        movePlayerUp();
        break;
      case 2:
        movePlayerDown();
        break;
      case 3:
        movePlayerLeft();
        break;
      case 4:
        movePlayerRight();
        break;
      }
    }

  void movePlayerDown() {
    if (wallAt(playerPosition.x, playerPosition.y+1)) {
      // Wall at this location
    } else {
      // No wall at this location
      playerPosition.y++;
    }
  }

  void movePlayerLeft() {
    if (wallAt(playerPosition.x-1, playerPosition.y)) {
      // Wall at this location
    } else {
      // No wall at this location
      playerPosition.x--;
    }
  }

  void movePlayerRight() {
    if (wallAt(playerPosition.x+1, playerPosition.y)) {
      // Wall at this location
    } else {
      // No wall at this location
      playerPosition.x++;
    }
  }

  /*
   * Checks the matrix for a wall at the specified position
   */
  bool wallAt(int x, int y) {
    return mazeMatrix[x][y] == 1;
  }

  /*
   * Moves the player to an empty spot.
   */
  void spawnPlayer() {
    if (mazeMatrix[0][0] == 0) {
      playerPosition = {0, 0};
    } else if (mazeMatrix[7][0] == 0) {
      playerPosition = {7, 0};
    } else if (mazeMatrix[0][7] == 0) {
      playerPosition = {0, 7};
    } else if (mazeMatrix[7][7] == 0) {
      playerPosition = {7, 7};
    }
  }

  /*
   * Loads the maze from an array of bytes into an array of arrays.
   * 
   * maze - an array of bytes representing the maze for loading into the matix.
   */
  void loadMaze(byte maze[8]) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (maze[x] &  1<<(7-y)) {
          mazeMatrix[x][y] = 1;
        } else {
          mazeMatrix[x][y] = 0;
        }
      }
    }
  }

  /*
   * Save the maze into an array of bytes with the player.
   * 
   * maze - the array of bytes to save maze information to for displaying.
   */
  void saveMaze(byte maze[8]) {
    for (int x = 0; x < 8; x++) {
      byte row = 0;
      for (int y = 0; y < 8; y++) {
        row = row << 1;
        row |= mazeMatrix[x][y];
      }
      maze[x] = row;
    }
  }

  /*
   * Prints a maze to the console
   */
  void printMaze(byte maze[8]) {
    Serial.println();
    for (int row = 0; row < 8; row++) {
      Serial.println(maze[row], BIN);
    }
    Serial.println();
  }

};

 //////////////////////////////////////////////  MAZE WALLS   ////////////////////////
void setup() {
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,10);  // Set intensity levels
  lc.setIntensity(1,10);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lastTick = millis();
  pinMode(pinJoyX, INPUT);
  pinMode(pinJoyY, INPUT);
  playFrame();
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

void insertDoor(int wall, int space) {
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
  mazeReset();
  genDoors();
  genInlineMaze();

  // Rotate and/or flip maze
  int manu = random(0,4);
  while (manu > 0) {
    rotateMaze();
    manu -= 1;
    }
}

void updateDisplay() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, mazeWalls[i]);
    }
  }

void genInlineMaze() {
  for (int row = 3; row < 6; row +=2) {
    mazeWalls[row] = ~(1<<random(1,7));
    }
  }

void togglePlayerPosition(int x, int y) {
    mazeWalls[x] ^= (1<<y);
  }

SAMazeModel player = SAMazeModel();

void loop() {
  unsigned long endTime;
  unsigned long startTime = millis();
  playFrame();
  player.loadMaze(mazeWalls);
  player.spawnPlayer();
  while (true) { // while the game is still going
    if (millis()-lastTick > 500) {
      if (millis()-lastTick > 250) {
        togglePlayerPosition(player.playerPosition.x, player.playerPosition.y);
        }
      updateDisplay();
      player.movePlayer();
      lastTick = millis();
      }    
    timer.updateTime(); 
    }
  endTime = millis();
  while (true) {
    timer.displayTime((int)(endTime-startTime));
    }
}
