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




void setupMaze() {
  // put your setup code here, to run once:
  SAMazeModel mazeModel = SAMazeModel();
  //mazeModel.loadMaze(sampleMaze);  // Load the sample maze into the arrayMaze
  //mazeModel.saveMaze(outputMaze);  // Save the arrayMaze to the output maze
  //mazeModel.printMaze(outputMaze);
  
}










