#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int shoulder = 0, elbow = 0;

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
  glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 1.0, 0.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f (1.0, 0.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glColor3f (0.0, 1.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (int key, int x, int y)
{
   switch (key) {
      case GLUT_KEY_LEFT:   
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case GLUT_KEY_RIGHT:
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutSpecialFunc(keyboard);
   glutMainLoop();
   return 0;
}
