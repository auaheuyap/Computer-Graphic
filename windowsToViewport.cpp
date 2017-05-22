#include <iostream>
# include <conio.h>
# include <graphics.h>

#define PI 3.14159265
#define ESC 0x1b 

using namespace std;

typedef float matrix [3] [3] ;
typedef float matrixkor [3] [1];

typedef struct { 
        int x, y; 
        } titik;

void setidentity(matrix m) /* Setting matrix identitas untuk matrix 3x3*/
{
int i, j;
for (i=0; i<3; i++) for (j=0; j<3; j ++) {if(i==j)m[i][j]=1;else m[i][j]=0;}
}



void matrixmultiply3 (matrix a, matrix b)/* Perkalian Matrix a ke Matrix b, hasil disimpan pada Matrix b*/
{
int r,c,i,j;
matrix tmp;
for (r = 0; r < 3; r++)
for (c = 0; c < 3; c++)
tmp[r][c] =a[r][0]*b[0][c]+a[r][1]*b[1][c]+a[r][2]*b[2][c];
for (r = 0; r < 3; r++)
for (c = 0; c < 3; c++)
b[r][c]=tmp[r][c];
}

void matrixmultiply31 (matrix a, matrixkor b)/* Perkalian Matrix a ke Matrix b, hasil disimpan pada Matrix b*/
{
int r,c,i,j;
matrix tmp;
for (r = 0; r < 3; r++)
tmp[r][0] =a[r][0]*b[0][0]+a[r][1]*b[0][1]+a[r][2]*b[0][2];

for (r = 0; r < 3; r++)
b[r][0]=tmp[r][0];
}

void Pause()
{
  int c;
  c = getch();                          /* Read a character from kbd    */
  if( ESC == c ){                       /* Does user wish to leave?     */
    closegraph();                       /* Change to text mode          */
    exit( 1 );                          /* Return to OS                 */
  }
  if( 0 == c ){                         /* Did use hit a non-ASCII key? */
    c = getch();                        /* Read scan code for keyboard  */
  }

  cleardevice();                        /* Clear the screen             */
}

void print(matrix a)                 /* Print matrix*/
{
int i,j;
for(i=0;i<3;i++){
for(j=0;j<3;j++)cout<<a[i][j]<<" ";
cout<<endl;
}
cout<<endl;
}

void print13(matrixkor a)                 /* Print matrix*/
{
int i;
for(i=0;i<3;i++)
cout<<a[i][0]<<endl;
cout<<endl;
}

int main()
{
    float xvmin,yvmin,sx,sy,ywmin,xwmin,xw,yw,xwmax,ywmax,xvmax,yvmax,xv,yv,centerx,centery,sx1,sx2,sx3,sy1,sy2,sy3;   
	xwmin=0;ywmin=0;xwmax=500;ywmax=500;
    initwindow( xwmax , ywmax , "window",xwmin,ywmin );
	
	
	/*segitiga*/
	sx1=20;sy1=300;
	sx2=450;sy2=450;
	sx3=270;sy3=350;
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);    
    
    Pause();
    closegraph();
    
    /*window to viewport*/
    xvmin=100;yvmin=100;xvmax=200;yvmax=200;
    initwindow( xvmax , yvmax , "viewport",xvmin,yvmin );
    
    
    matrix vmin,s,minw;
    matrixkor utama;
    utama[0][0]=sx1;utama[1][0]=sy1;utama[2][0]=1;
    
    setidentity(vmin);
    vmin[0][2]=xvmin;vmin[1][2]=yvmin;
    
    sx=(xvmax-xvmin)/(xwmax-xwmin);
    sy=(yvmax-yvmin)/(ywmax-ywmin);
    setidentity(s);
    s[0][0]=sx;s[1][1]=sy;
    
    setidentity(minw);
    minw[0][2]=-xwmin;minw[1][2]=-ywmin;
    
    print(vmin);
    print(s);
    print(minw);
    print13(utama);
    
    matrixmultiply3(vmin,s);
    matrixmultiply3(s,minw);
    matrixmultiply31(minw,utama);
    
    print(vmin);
    print(s);
    print(minw);
    print13(utama);
    
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utama[0][0]=sx2;utama[1][0]=sy2;
    matrixmultiply31(minw,utama);
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utama[0][0]=sx3;utama[1][0]=sy3;
    matrixmultiply31(minw,utama);
    sx3=utama[0][0];
    sy3=utama[1][0];
    
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);  
    
    
    getch();
    return 0;

}
