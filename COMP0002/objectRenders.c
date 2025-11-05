#include "graphics.h"
#include "displayer.h"
#include <stdlib.h>

const int width = 600;
const int height = 600;
const int waitTime = 1000;
const int squareSize = 60;
const int moveDistance = 8;
int xCoords[] = {0, 0 ,0};
int yCoords[] = {0, 0, 0};

// Set the background contents, which is then always displayed and
// left unmodified.
void drawBackground()
{
  background(); // Must draw on the background layer.
  setColour(black);
  int * tile_count = tile_coords();
  //drawing the horizontal lines for the tiles
  for(int i=0;i<tile_count[0];i++){
    drawLine(0,i*height/tile_count[0],width,i*height/tile_count[0]);
  }
  //drawing the vertical lines for the tiles
  for(int i=0;i<tile_count[1];i++){
    drawLine(i*width/tile_count[1],0,i*width/tile_count[1],height);
  }
  free(tile_count);
}

// Update the foreground layer to display the triangle in it's new positions.
void move_horizontal(int *x,int direction)
{
  // Clear the existing content, otherwise triangles will just be added
  //  to what is already there.
  int * tile_count = tile_coords();
  if (direction){
    for(int i=0;i<3;i++) x[i] = x[i] + width/tile_count[1];
  }
  else
  {
    for(int i=0;i<3;i++) x[i] = x[i] - width/tile_count[1];
  }
  
  clear();
  fillPolygon(3,x,yCoords);
  free(tile_count);
  sleep(600);
}
void move_vertical(int *y,int direction)
{
    int *tile_count = tile_coords();
    if (!tile_count) return;                 /* allocation/read failed */

    int rows = tile_count[0] > 0 ? tile_count[0] : 1; /* avoid div-by-zero */
    int delta = height / rows;

    if (direction) {
        for (int i = 0; i < 3; ++i) y[i] -= delta;
    } else {
        for (int i = 0; i < 3; ++i) y[i] += delta;
    }

    clear();
    fillPolygon(3, xCoords, y);
    free(tile_count);

    sleep(600);
}
// ...existing code...
void spawnTriangle(void)
{
    int *tile_count = tile_coords();
    if (!tile_count) return;

    int rows = tile_count[0] > 0 ? tile_count[0] : 1;
    int cols = tile_count[1] > 0 ? tile_count[1] : 1;

    /* last row (0-based) */
    int row_idx = rows - 1;

    /* choose column:
       - odd cols: middle column (0-based cols/2)
       - even cols: "tile numbered by total tiles/2" interpreted as 1-based cols/2,
         converted to 0-based => cols/2 - 1
    */
    int col_idx;
    if (cols % 2 == 1) {
        col_idx = cols / 2;
    } else {
        col_idx = cols / 2 - 1;
        if (col_idx < 0) col_idx = 0;
    }

    int tile_w = width / cols;
    int tile_h = height / rows;

    int cx = col_idx * tile_w + tile_w / 2;
    int cy = row_idx * tile_h + tile_h / 2;

    double min_dim = (tile_w < tile_h) ? tile_w : tile_h;
    double tri_size = 0.7 * min_dim; /* ~70% of tile */

    int half_base = (int)(tri_size * 0.5);
    int tri_h = (int)(tri_size * 0.86602540378); /* approx sqrt(3)/2 */

    /* top, bottom-left, bottom-right */
    xCoords[0] = cx;
    yCoords[0] = cy - tri_h / 2;
    xCoords[1] = cx - half_base;
    yCoords[1] = cy + tri_h / 2;
    xCoords[2] = cx + half_base;
    yCoords[2] = cy + tri_h / 2;

    free(tile_count);
}
// ...existing
    




// Control the animation step-by-step
int main(void)
{
  setWindowSize(width+1, height+1);
  drawBackground();
  foreground();
  spawnTriangle();
  for (int i=0;i<10;i++){
  move_horizontal(xCoords,1);
  move_vertical(yCoords,0);
  move_horizontal(xCoords,0);
  move_vertical(yCoords,1);
  }
  return 0;
}