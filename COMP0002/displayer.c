#include "readFile.h"
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include <stdlib.h>
#include <string.h>
int *tile_coords(){
    int *tile_counts = malloc(2*sizeof(int));
    size_t count = 0;
    char **lines = readFile("map.txt",&count);
    int horizontal_tile_count = (int)count;  // Number of rows (vertical lines needed)
    int vertical_tile_count = (int)round(strlen(lines[0])/2.0);  // Number of columns (horizontal lines needed)
    
    tile_counts[0] = horizontal_tile_count;  // rows
    tile_counts[1] = vertical_tile_count;    // columns
    
    free_lines(lines);
    return tile_counts;
}
void spawnTriangle(int* x,int *y,int width,int height)
{
    int *tile_count = tile_coords();
    int rows = tile_count[0];
    int cols = tile_count[1];

    int tile_w = width / cols;
    int tile_h = height / rows;
    
    // Spawn triangle in center tile
    int row_idx = rows / 2;
    int col_idx = cols / 2;
    
    // Calculate the actual center using the tile grid
    int cx = col_idx * tile_w + tile_w / 2;
    int cy = row_idx * tile_h + tile_h / 2;
    
    
    int half_base = (int)(tile_h * 0.35); // 70% of tile height
    int tri_h = (int)(tile_w * 0.6);      // 60% of tile width
    
    /* top, bottom, right - base parallel to left side, apex pointing right */
    x[0] = cx - tri_h / 2;
    y[0] = cy - half_base;
    x[1] = cx - tri_h / 2;
    y[1] = cy + half_base;
    x[2] = cx + tri_h / 2;
    y[2] = cy;
    
    fillPolygon(3,x,y);
    free(tile_count);
    sleep(600);
}
void drawBackground(int height, int width)
{
  background(); // Must draw on the background layer.
  clear();
  setColour(black);
  int * tile_count = tile_coords();
  
  //drawing the horizontal lines for the tiles
  for(int i=0; i<=tile_count[0]; i++){  // Changed < to <=
    drawLine(0, i*height/tile_count[0], width, i*height/tile_count[0]);
  }
  //drawing the vertical lines for the tiles
  for(int i=0; i<=tile_count[1]; i++){  // Changed < to <=
    drawLine(i*width/tile_count[1], 0, i*width/tile_count[1], height);
  }
  free(tile_count);
}
void spawnMarker(int tile_row,int tile_col,int height,int width){
    background();
    setColour(red);
    int *tile_count = tile_coords();
    int tile_w = width / tile_count[1];
    int tile_h = height / tile_count[0];
    
    int center_x = tile_col * tile_w + tile_w / 2;
    int center_y = tile_row * tile_h + tile_h / 2;
    int marker_size = (tile_w < tile_h ? tile_w : tile_h) / 2;
    fillOval(center_x - marker_size / 2, center_y - marker_size / 2, marker_size, marker_size);
    free(tile_count);
}

void spawnObstacle(int tile_row,int tile_col,int height,int width){
    background();
    setColour(darkgray);
    int *tile_count = tile_coords();
    int tile_w = width / tile_count[1];
    int tile_h = height / tile_count[0];
    
    // Top-left corner of the tile
    int tile_x = tile_col * tile_w;
    int tile_y = tile_row * tile_h;
    
    // Fill the entire tile
    fillRect(tile_x, tile_y, tile_w, tile_h);
    free(tile_count);
}


// New function to load map and spawn objects based on map.txt values
void loadMapAndSpawn(int height, int width) {
    // First draw the background grid
    drawBackground(height, width);
    
    size_t count = 0;
    char **lines = readFile("map.txt", &count);
    
    if (!lines) return;
    
    // Parse the map and spawn objects based on values
    for (int row = 0; row < (int)count; row++) {
        char *line = lines[row];
        char *token = strtok(line, ",");
        int col = 0;

        while (token != NULL) {
            int value = atoi(token);
            
            if (value == 1) {
                // Spawn marker at this tile
                spawnMarker(row, col, height, width);
            } else if (value == 2) {
                // Spawn obstacle at this tile
                spawnObstacle(row, col, height, width);
            }
            // 0 or other values = empty tile
            
            col++;
            token = strtok(NULL, ",");
        }
    }
    
    free_lines(lines);
}









