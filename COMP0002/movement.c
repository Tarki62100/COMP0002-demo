#include "displayer.h"
#include <stdlib.h>
#include "graphics.h"
#include <math.h>


void move_horizontal(int *x,int *y,int width, int direction)
{
  // Clear the existing content, otherwise triangles will just be added
  //  to what is already there.
  int * tile_count = tile_coords();
  int col_width = width/tile_count[1];
  if (direction){
    for(int i=0;i<3;i++) x[i] += col_width;
  }
  else
  {
    for(int i=0;i<3;i++) x[i] -= col_width;
  }
  clear();
  fillPolygon(3,x,y);
  free(tile_count);
  sleep(600);
}
void move_vertical(int *x, int *y, int height, int direction)
{
    int *tile_count = tile_coords();
    int row_height = height / tile_count[0];

    if (direction==1) {
        for (int i = 0; i < 3; ++i) y[i] -= row_height;
    } else {
        for (int i = 0; i < 3; ++i) y[i] += row_height;
    }

    clear();
    fillPolygon(3, x, y);
    free(tile_count);

    sleep(600);
}
void move_left(int *x,int *y,int width){
    move_horizontal(x,y,width,0);
}
void move_right(int *x,int *y,int width){
    move_horizontal(x,y,width,1);
}
void move_up(int *x, int *y, int height){
    move_vertical(x, y, height, 1);
}
void move_down(int *x, int *y, int height){
    move_vertical(x, y, height, 0);
}

// Calculate distance between triangle center and marker
double calculate_distance(int *x, int *y, int *markerCoord, int width, int height) {
    int *tile_count = tile_coords();
    int tile_w = width / tile_count[1];
    int tile_h = height / tile_count[0];
    
    int tri_cx = (x[0] + x[1] + x[2]) / 3;
    int tri_cy = (y[0] + y[1] + y[2]) / 3;
    
    int marker_x = markerCoord[1] * tile_w + tile_w / 2;
    int marker_y = markerCoord[0] * tile_h + tile_h / 2;
    
    free(tile_count);
    
    double dx = tri_cx - marker_x;
    double dy = tri_cy - marker_y;
    return sqrt(dx*dx + dy*dy);
}

// Find index of closest marker
int find_closest_marker(int *x, int *y, int (*markerCoords)[2], int visited[], int markerCount, int width, int height) {
    int closest = -1;
    double min_dist = -1;
    
    for (int i = 0; i < markerCount; i++) {
        if (!visited[i]) {
            double dist = calculate_distance(x, y, markerCoords[i], width, height);
            if (closest == -1 || dist < min_dist) {
                min_dist = dist;
                closest = i;
            }
        }
    }
    
    return closest;
}

void move_towards_marker(int *x, int *y, int width, int height, int *markerCoords){
    int *tile_count = tile_coords();
    int tile_w = width / tile_count[1];
    int tile_h = height / tile_count[0];

    int target_x = markerCoords[1] * tile_w + tile_w / 2;
    int target_y = markerCoords[0] * tile_h + tile_h / 2;

    // Keep moving until we reach the marker
    while (1) {
        int tri_cx = (x[0] + x[1] + x[2]) / 3;
        int tri_cy = (y[0] + y[1] + y[2]) / 3;

        // Check if we're close enough to the target (within half a tile)
        int dx = abs(tri_cx - target_x);
        int dy = abs(tri_cy - target_y);
        
        if (dx < tile_w / 2 && dy < tile_h / 2) {
            break;  // We've reached the marker
        }

        // Move horizontally
        if (tri_cx < target_x - tile_w / 2) {
            move_right(x, y, width);
        } else if (tri_cx > target_x + tile_w / 2) {
            move_left(x, y, width);
        }

        // Recalculate position after horizontal move
        tri_cx = (x[0] + x[1] + x[2]) / 3;
        tri_cy = (y[0] + y[1] + y[2]) / 3;

        // Move vertically
        if (tri_cy < target_y - tile_h / 2) {
            move_down(x, y, height);
        } else if (tri_cy > target_y + tile_h / 2) {
            move_up(x, y, height);
        }
    }

    free(tile_count);
}