#pragma once
int *tile_coords();
void spawnTriangle(int* x,int *y,int width,int height);
void drawBackground(int height, int width);
void spawnMarker(int tile_row,int tile_col,int height,int width);
void spawnObstacle(int tile_row,int tile_col,int height,int width);
void loadMapAndSpawn(int height, int width);