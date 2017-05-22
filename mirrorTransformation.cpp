#include <stdio.h>
#include <iostream>
#include <math.h>
#include <graphics.h>

#define PI 3.14159265
#define ESC 0x1b  

typedef float Matrix3x3 [3] [3] ;
Matrix3x3 utama;                        


typedef struct { 
        float x, y; 
        } wcPt2;

using namespace std;

void matrix3x3SetIdentity (Matrix3x3 m) /* Setting matrix identitas untuk matrix 3x3*/
{
int i, j;
for (i=0; i<3; i++) for (j=0; j<3; j ++) {if(i==j)m[i][j]=1;else m[i][j]=0;}
}

void utamaSetIdentity(int x,int y,Matrix3x3 m)/* Input kordinat x y pada matrix utama*/
{
m[0][0]=x;
m[1][0]=y;
m[2][0]=1;
}

void matrix3x3PreMultiply (Matrix3x3 a, Matrix3x3 b)/* Perkalian Matrix a ke Matrix b, hasil disimpan pada Matrix b*/
{
int r,c,i,j;
Matrix3x3 tmp;
for (r = 0; r < 3; r++)
for (c = 0; c < 3; c++)
tmp[r][c] =a[r][0]*b[0][c]+a[r][1]*b[1][c]+a[r][2]*b[2][c];
for (r = 0; r < 3; r++)
for (c = 0; c < 3; c++)
b[r][c]=tmp[r][c];
}


void translate2 (int tx, int ty)/*operasi translasi*/
{
Matrix3x3 m;
matrix3x3SetIdentity (m);
m[0][2] = tx;
m[1][2] = ty;
matrix3x3PreMultiply (m, utama);
}

void rotate2 (float a, wcPt2 refPt)/*operasi rotasi*/
{
Matrix3x3 m;
matrix3x3SetIdentity (m);
a=a*PI/180;
m[0] [0] = cos (a);
m[0] [1] = -sin (a);
m[0] [2] = refPt.x * (1 - cos (a)) + refPt.y * sin (a);
m[1] [0] = sin (a);
m[1] [1] = cos (a);
m[1] [2] = refPt.y * (1 - cos (a)) - refPt.x * sin (a) ;
matrix3x3PreMultiply (m, utama);
}

void reflecty()/*operasi refleksi pada y axis (x=0)*/
{
Matrix3x3 m;
matrix3x3SetIdentity (m);
m[0][0]=-1;
matrix3x3PreMultiply (m, utama);
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

float radius(float x1,float x2,float y1,float y2)/*menghitung panjang garis*/
{    
return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

void print(Matrix3x3 a)                 /* Print matrix*/
{
int i,j;
for(i=0;i<3;i++){
for(j=0;j<3;j++)cout<<a[i][j]<<" ";
cout<<endl;
}
cout<<endl;
}

int main( )
{
    int i,j,gradien;
    float x1,y1,x2,y2,centerx,centery,X1,X2,Y1,Y2,sx1,sx2,sx3,sy1,sy2,sy3;   
	initwindow( 640 , 480 , "Refleksi" );
	
	/*segitiga*/
	sx1=300;sy1=300;
	sx2=450;sy2=450;
	sx3=270;sy3=350;
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
    
    /*garis sembarang PQ*/
    x1=getmaxx()/2-100;
    y1=getmaxy()/2+100;
    x2=getmaxx()/2+100;
    y2=getmaxy()/2-100;
    centerx=(x1+x2)/2;
    centery=(y1+y2)/2;
    
    bool norotate=false;
    if(x2-x1==0)norotate=true;
    else gradien=(y2-y1)/(x2-x1);
    
    line(x1,y1,x2,y2);
    
    wcPt2 refPt = {centerx, centery}; //pusat rotasi ditengah garis
    
	Pause();
	
	/*mencari sudut rotasi untuk axis y (dx=0)*/
	int r=radius(x1,x2,y1,y2);
	float sudut,nilai;
	X1=centerx;
	X2=centerx;
	Y1=centery-r/2;
	Y2=centery+r/2;
	
	if (norotate)sudut=0;
	else if(gradien<0){
	if(y1>y2)nilai=(centery-y1)/(r/2);
	else nilai=(centery-y2)/(r/2);
	sudut=-1*(180-acos(nilai)*180/PI);
    }
    else {
    if(y1<y2)nilai=(centery-y1)/(r/2);
	else nilai=(centery-y2)/(r/2);
	sudut=acos(nilai)*180/PI;
    }
    
    /*rotasi(+a)*/
	matrix3x3SetIdentity (utama);
	
	utamaSetIdentity(sx1,sy1,utama);
    rotate2 (sudut, refPt);
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utamaSetIdentity(sx2,sy2,utama);
    rotate2 (sudut, refPt);
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utamaSetIdentity(sx3,sy3,utama);
    rotate2 (sudut, refPt);
    sx3=utama[0][0];
    sy3=utama[1][0];
	
	line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
	
    utamaSetIdentity(x1,y1,utama);
    rotate2 (sudut, refPt);
    x1=utama[0][0];
    y1=utama[1][0];
    
    utamaSetIdentity(x2,y2,utama);
    rotate2 (sudut, refPt);
    x2=utama[0][0];
    y2=utama[1][0];
    
    line(x1,y1,x2,y2);
    
    Pause();

    /*translasi(-x,-y)*/
    
    int transx,transy;
    if(x1<x2)transx=x1;else transx=x2;
    if(y1<y2)transy=y1;else transy=y2;
    utamaSetIdentity(x1,y1,utama);
    translate2 (-transx, -transy);
    x1=utama[0][0];
    y1=utama[1][0];
    
    utamaSetIdentity(x2,y2,utama);
    translate2 (-transx, -transy);
    x2=utama[0][0];
    y2=utama[1][0];
    
    utamaSetIdentity(sx1,sy1,utama);
    translate2 (-transx, -transy);
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utamaSetIdentity(sx2,sy2,utama);
    translate2 (-transx, -transy);
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utamaSetIdentity(sx3,sy3,utama);
    translate2 (-transx, -transy);
    sx3=utama[0][0];
    sy3=utama[1][0];
    
    //cout<<sx1<<" "<<sy1<<endl<<sx2<<" "<<sy2<<endl<<sx3<<" "<<sy3<<endl;
    
    line(x1,y1,x2,y2);
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
    
    Pause();
    
    /*refleksi sumbu terhadap axis y (x=0)*/

    utamaSetIdentity(sx1,sy1,utama);
    reflecty ();
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utamaSetIdentity(sx2,sy2,utama);
    reflecty ();
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utamaSetIdentity(sx3,sy3,utama);
    reflecty ();
    sx3=utama[0][0];
    sy3=utama[1][0];
    
    line(x1,y1,x2,y2);
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
    
    Pause();
	
	/*translasi(+x,+y)*/
    utamaSetIdentity(x1,y1,utama);
    translate2 (transx, transy);
    x1=utama[0][0];
    y1=utama[1][0];
    
    utamaSetIdentity(x2,y2,utama);
    translate2 (transx, transy);
    x2=utama[0][0];
    y2=utama[1][0];
    
    utamaSetIdentity(sx1,sy1,utama);
    translate2 (transx, transy);
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utamaSetIdentity(sx2,sy2,utama);
    translate2 (transx, transy);
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utamaSetIdentity(sx3,sy3,utama);
    translate2 (transx, transy);
    sx3=utama[0][0];
    sy3=utama[1][0];
    
    line(x1,y1,x2,y2);
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
    
    Pause();
    
    /*rotasi(-a)*/
    utamaSetIdentity(sx1,sy1,utama);
    rotate2 (-sudut, refPt);
    sx1=utama[0][0];
    sy1=utama[1][0];
    
    utamaSetIdentity(sx2,sy2,utama);
    rotate2 (-sudut, refPt);
    sx2=utama[0][0];
    sy2=utama[1][0];
    
    utamaSetIdentity(sx3,sy3,utama);
    rotate2 (-sudut, refPt);
    sx3=utama[0][0];
    sy3=utama[1][0];
	
    utamaSetIdentity(x1,y1,utama);
    rotate2 (-sudut, refPt);
    x1=utama[0][0];
    y1=utama[1][0];
    
    utamaSetIdentity(x2,y2,utama);
    rotate2 (-sudut, refPt);
    x2=utama[0][0];
    y2=utama[1][0];
    
    line(x1,y1,x2,y2);
    line(sx1,sy1,sx2,sy2);
    line(sx2,sy2,sx3,sy3);
    line(sx3,sy3,sx1,sy1);
    
    Pause();
	
	return( 0 );
}
