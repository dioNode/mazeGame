

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

class SAMazeModel {

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



/*
 * Loads the maze from an array of bytes into an array of arrays.
 * 
 * maze - an array of bytes representing the maze for display.
 * matrix - an array of integer arrays to load maze information into.
 */
void loadMaze(byte maze[8], int matrix[8][8]) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (maze[x] &  1<<(7-y)) {
        matrix[x][y] = 1;
      } else {
        matrix[x][y] = 0;
      }
    }
  }
}

/*
 * Save the maze into an array of bytes with the player.
 * 
 * matrix - an array of integer arrays to get maze information from.
 * maze - the array of bytes to save maze information to for displaying.
 */
void saveMaze(int matrix[8][8], byte maze[8]) {
  for (int x = 0; x < 8; x++) {
    byte row = 0;
    for (int y = 0; y < 8; y++) {
      row = row << 1;
      row |= matrix[x][y];
    }
    maze[x] = row;
  }
}

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Maze Model");
  
  int arrayMaze[8][8];              // Stores the maze representation
  loadMaze(sampleMaze, arrayMaze);  // Load the sample maze into the arrayMaze
  arrayMaze[4][4] = 1;              // Make a change to the maze
  saveMaze(arrayMaze, outputMaze);  // Save the arrayMaze to the output maze
  
    
}

void loop() {
  // put your main code here, to run repeatedly:
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










