#ifndef MAZEWALLS_H_
#define MAZEWALLS_H_

#include <LedControl.h>
#include <Arduino.h>

#define DEFAULTMAZE {0, 0xFF, B10000001, B10000001, B10000001, B10000001, B10000001, 0xFF}

class MazeWalls {
  public:
  	MazeWalls();
  	void makeFrame();
  	bool isWallAt();
  private:
  	LedControl lc;
  	char mazeWalls[8];
  	void insertDoor(int wall, int space);
    void genDoors();
    void mazeReset();
    void rotateMaze();
    void genInlineMaze();
}

#endif