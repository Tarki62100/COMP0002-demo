#include "graphics.h"
#include "displayer.h"

const int width = 600;
const int height = 600;
const int waitTime = 1000;
const int squareSize = 60;
const int moveDistance = 8;

// Set the background contents, which is then always displayed and
// left unmodified.
void drawBackground()
{
  background(); // Must draw on the background layer.
  setColour(red);
  int * tile_count = tile_coords("map.txt");
  for(int i=0;i<tile_count[0];i++){
    drawLine(0,i*height/tile_count[0],width,(i+1)*width/tile_count[0]);
  }
  // An example of drawing a polygon given the coordinates of each
  // corner.
  int xCoords[] = {150, 450, 150};
  int yCoords[] = {50, 550, 250};
  fillPolygon(3, xCoords, yCoords);
}

// Update the foreground layer to display the square in a new position
void update(int x, int y)
{
  // Clear the existing content, otherwise squares will just be added
  // and to what is already there.
  clear();
  fillRect(x, y, squareSize, squareSize);
}

// Control the animation step-by-step
void move()
{
  // The animated shape is on the foreground (top) layer, which must be
  // selected.
  foreground();
  setColour(blue);
  int x = 20;
  int y = 100;
  // A loop to control what changes for each step of the animation
  for (int n = 0; n < 60; n++)
  {
    // Move the square to the next position
    update(x, y);
    // Modify the coordinates for the next iteration.
    x += moveDistance;
    y += moveDistance / 2;
    // Pause execution for a short while to slow the movement down, otherwise
    // the animation will happen so fast it can't be seen.
    sleep(waitTime);
  }
}

int main(void)
{
  setWindowSize(width, height);
  drawBackground();
  move();
}