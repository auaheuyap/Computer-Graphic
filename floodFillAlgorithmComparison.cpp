#include "graphics.h"
#include <conio.h>
#include <math.h>

void MyFloodFill(int x,int y,int color1,int color2,int replaced)
{

    if(getpixel(x,y)==replaced)
    {
        if(x%10<5)putpixel(x,y,color1);
        else putpixel(x,y,color2);
        MyFloodFill(x-1,y,color1,color2,replaced);
        //MyFloodFill(x-1,y+1,color,replaced);
        MyFloodFill(x,y+1,color1,color2,replaced);
        //MyFloodFill(x+1,y+1,color,replaced);
        MyFloodFill(x+1,y,color1,color2,replaced);
        //MyFloodFill(x+1,y-1,color,replaced);
        MyFloodFill(x,y-1,color1,color2,replaced);
        //MyFloodFill(x-1,y-1,color,replaced);
    }
}

int main(void)
{

   int wid1, wid2;

   /* initialize graphics windows */
   wid1 = initwindow(500, 500, "my floodfill");
   wid2 = initwindow(500, 500, "library floodfill",600,0);



   int left,top,right,bottom,centerx,centery;
   
   /*my floodfill */ 
   setcurrentwindow(wid1);
   left = getmaxx() / 2 - 100;
   top = getmaxy() / 2 - 100;
   right = getmaxx() / 2 + 100;
   bottom = getmaxy() / 2 + 100;
   centerx=(right+left)/2;
   centery=(bottom+top)/2;

   rectangle(left,top,right,bottom);

   MyFloodFill(centerx,centery,15,8,0);
   
   /*library foodfill*/
   setcurrentwindow(wid2);
   left = getmaxx() / 2 - 100;
   top = getmaxy() / 2 - 100;
   right = getmaxx() / 2 + 100;
   bottom = getmaxy() / 2 + 100;
   
   rectangle(left,top,right,bottom);
   floodfill(centerx,centery,15);



   /* clean up */
   getch();
   return 0;

}
