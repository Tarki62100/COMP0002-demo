#include "readFile.h"
#include <stdio.h>

int main(void){
    size_t count = 0;
    char **lines = readFile("map.txt",&count);
    
    for(size_t i = 0;i<count; i++){
        printf("%s",lines[i]);
    }
    free_lines(lines);
    return 0;
}
