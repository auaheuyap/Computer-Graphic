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

void windowtoviewport(int x,int y);

int main()
{
    initwindow( 640 , 480 , "Affine" );
    line(-2,0,-1,8);
    line(-1,8,1,8);
    line(1,8,2,0);
    line(2,0,-2,0);
    
    
    getch();
    return 0;

}
