#pragma once
void move_horizontal(int *x,int *y,int width, int direction);
void move_vertical(int *y,int *x,int height,int direction);
void move_left(int *x,int *y,int width);
void move_right(int *x,int *y,int width);
void move_up(int *x,int *y,int height);
void move_down(int *x,int *y,int height);
void move_towards_marker(int *x, int *y, int width, int height, int *markerCoords);
double calculate_distance(int *x, int *y, int *markerCoord, int width, int height);
int find_closest_marker(int *x, int *y, int markerCoords[][2], int visited[], int markerCount, int width, int height);