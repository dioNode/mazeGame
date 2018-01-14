/*
 * Maze Model
 */

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



void setupMaze() {
  // put your setup code here, to run once:
  //SAMazeModel mazeModel = SAMazeModel();
  //mazeModel.loadMaze(sampleMaze);  // Load the sample maze into the arrayMaze
  //mazeModel.saveMaze(outputMaze);  // Save the arrayMaze to the output maze
  //mazeModel.printMaze(outputMaze);
  
}










