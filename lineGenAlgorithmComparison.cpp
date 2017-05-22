#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#include <graphics.h>

using namespace std;

void Bressenham(int x1,int y1,int const x2,int const y2){
     
    int delta_x(x2 - x1);
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = abs(delta_x) << 1;
    int delta_y(y2 - y1);
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = abs(delta_y) << 1;
 
    if(x1%10<5)putpixel(x1, y1,15);
 
    if (delta_x >= delta_y){
        int error(delta_y - (delta_x >> 1));
        while (x1 != x2){
            if ((error >= 0) && (error || (ix > 0))){
                error -= delta_x;
                y1 += iy;
            }
            error += delta_y;
            x1 += ix;
 
            if(x1%10<5)putpixel(x1, y1,15);
        }
    }
    else{
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2){
            if ((error >= 0) && (error || (iy > 0))){
                error -= delta_y;
                x1 += ix;
            }
            error += delta_x;
            y1 += iy;
            if(x1%10<5)putpixel(x1, y1,15);
        }
    }
}

void DDA(int xstart,int ystart,int xend,int yend){
     int step,k,dx,dy;
     double x_inc,y_inc,x,y;
     dx=xend-xstart;dy=yend-ystart;
     x=xstart;y=ystart;
     if(abs(dx) > abs(dy))step=abs(dx); else step=abs(dy);
     x_inc=dx/step;
     y_inc=dy/step;
     putpixel(ceil(x),ceil(y),15);
     for(k=1;k<=step;k++){
                          x=x+x_inc;
                          y=y+y_inc;
                          putpixel(ceil(x),ceil(y),15);
                          }
     }

void BressenhamDosen(int xa,int ya,int xb,int yb){
     int dx,p,dy,xEnd,x,y;
     dx=abs(xb-xa);
     dy=abs(yb-ya);
     p=2*dy-dx;
     
     if(xa>xb){x=xb;y=yb;xEnd=xa;}
     else {x=xa;y=ya;xEnd=xb;}
     
     putpixel(x,y,15);
     while(x<xEnd){
                   x=x+1;
                   if(p<0)p=p+2*dy;
                   else {y=y+1;p=p+2*dy-2*dx;}
                   putpixel(x,y,15);
                   }
     
     }

int main( )
{   
    
    int x1=0,y1=0,x2=1366,y2=768;
    
    /*Resolusi laptop saya 1366 x 768*/
    initwindow(1366,768,"GrafKom");
	while( !kbhit() ){
          //DDA(x1,y1,x2,y2);
          //BressenhamDosen(x1,y1,x2,y2);
          Bressenham(x1,y1,x2,y2);
          
          /*library c++*/
          //line(x1,y1,x2,y2);
          }
	closegraph( );
	return( 0 );
}
