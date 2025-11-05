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
    int horizontal_line_count=(int)round(strlen(lines[1])/2.0);
    int vertical_line_count=0;
    for(size_t i = 0;i<count; i++){
        vertical_line_count++;
    }
    tile_counts[0] = horizontal_line_count;
    tile_counts[1] = vertical_line_count;
    free_lines(lines);
    return tile_counts;
}








