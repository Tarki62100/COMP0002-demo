#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.c"
#include <math.h>
int main (void)
{
  void drawHouse(void);
  void drawOctagon(int,int,int);
  //drawOctagon(150,50,100);
  //drawHouse();
  int x[4] = {50, 100, 150, 200};
  int xHalf1[4] = {50,100,125,125};
  int xHalf2[4] = {125,125,150,200};
  int yHalf[4] = {50,25,25,50};
  int y[4] = {50, 25, 25, 50};  /* then call: drawPolygon(3, x, y); */
  drawPolygon(4,x,y);
  setColour(green);
  fillPolygon(4,xHalf1,yHalf);
  setColour(red);
  fillPolygon(4,xHalf2,yHalf);
  return 0;
}

void drawHouse(void)
{
  drawRect(50,100,200,150);
  drawLine(50,100,150,25);
  drawLine(150,25,250,100);
  drawRect(130,190,40,60);
  drawRect(70,195,40,30);
  drawRect(190,195,40,30);
  drawRect(70,125,40,30);
  drawRect(190,125,40,30);
}

void drawOctagon(int x,int y,int sidelength){
  drawLine(x,y,x+sidelength,y);
  drawLine(x+sidelength,y,x+sidelength*(1+1/sqrt(2)),y+sidelength*1/sqrt(2));
  drawLine(x+sidelength*(1+1/sqrt(2)),y+sidelength*1/sqrt(2),x+sidelength*(1+1/sqrt(2)),y+sidelength*(1+1/sqrt(2)));
  drawLine(x+sidelength*(1+1/sqrt(2)),y+sidelength*(1+1/sqrt(2)),x+sidelength,y+sidelength*(1+2/sqrt(2)));
  drawLine(x,y,x-sidelength*(1/sqrt(2)),y+sidelength*(1/sqrt(2)));
  drawLine(x-sidelength*(1/sqrt(2)),y+sidelength*(1/sqrt(2)),x-sidelength*(1/sqrt(2)),y+sidelength*(1+1/sqrt(2)));
  drawLine(x-sidelength*(1/sqrt(2)),y+sidelength*(1+1/sqrt(2)),x,y+sidelength*(1+2/sqrt(2)));
  drawLine(x,y+sidelength*(1+2/sqrt(2)),x+sidelength,y+sidelength*(1+2/sqrt(2)));
}