#include "graphics.h"
#include "displayer.h"
#include "movement.h"

const int width = 500;
const int height = 500;
int xCoords[] = {0, 0 ,0};
int yCoords[] = {0, 0, 0};
int markerCoords[][2] = {{0,0},{1,1},{2,3}};  // row, col
int markerCount = 3;
int obstacleCoords[][2] = {{0,1},{1,2}}; // row, col
int obstacleCount = 2;

int main(void)
{
  setWindowSize(width+1, height+1);
  loadMapAndSpawn(height, width);
  // Draw all markers on background
  spawnTriangle(xCoords, yCoords, width, height);
  return 0;
}