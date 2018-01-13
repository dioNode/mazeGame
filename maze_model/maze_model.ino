

#define MIN_WIDTH 0
#define MAX_WIDTH 7
#define MIN_HEIGHT 0
#define MAX_HEIGHT 7

/*
 * Describes a point that exists with a x and y.
 */
struct SAPoint {
  int x;
  int y;
};

/*
 * Returns the maze 
 */
void getMaze() {
  
}


class SAMazeGame {

  private:
    SAPoint playerPosition = {0,0};

  void setPlayerPosition(SAPoint pos) {
    playerPosition = pos;
  }

  SAPoint getPlayerPosition() {
    return playerPosition;
  }


  void movePlayerUp() {
    playerPosition.y++;
  }

  void movePlayerDown() {
    playerPosition.y--;
  }

  void movePlayerLeft() {
    playerPosition.x--;
  }

  void movePlayerRight() {
    playerPosition.x++;
  }
  
};

byte mazeWalls[] {
  B11111111,
  B10000001,
  B10010001,
  B10011001,
  B10011001,
  B10010001,
  B10000001,
  B11111111
};

byte mazeRender[] {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

int arrayMaze[8][8];  // An 8x8 matrix.

/*
 * Loads the maze from an array of bytes into an array of arrays.
 */
void loadMaze(byte maze[8]) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (maze[x] &  1<<(7-y)) {
        arrayMaze[x][y] = 1;
      } else {
        arrayMaze[x][y] = 0;
      }
    }
  }
}

/*
 * Save the maze into an array of bytes with the player.
 */
byte saveMaze() {
  for (int x = 0; x < 8; x++) {
    byte row = 0;
    for (int y = 0; y < 8; y++) {
      row = row << 1;
      row |= arrayMaze[x][y];
    }
    mazeRender[x] = row;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loadMaze(mazeWalls);
  Serial.println();
//  for (int x = 0; x < 8; x++) {
//    for (int y = 0; y < 8; y++) {
//      Serial.print(arrayMaze[x][y]);
//    }
//    Serial.println();
//  }
  saveMaze();
  for (int x = 0; x<8; x++) {
    Serial.println(mazeRender[x], BIN);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}










