#include <stdio.h>
#include <stdlib.h>
readMap(FILE a){
    FILE *map;
    map = fopen(a,"r");
    char mapContents[100];
    fgets(&mapContents,100,map);
    printf("%s",mapContents);
}
int main(void){
    readmap(FILE);
    readmap("map.txt");



}

