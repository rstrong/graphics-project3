#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>

// The beginnings of ours...
#include <mathutil.h>
#include <mesh.h>
#include <primitive.h>


int WIDTH = 640;
int HEIGHT = 480;

void main_reshape(int width, int height)
{
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,width,height,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void main_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(1.0f);

  glBegin(GL_POINTS);
  glColor3f(0.5,0.5,0.5);
  glVertex3f(0,0,0);
  glVertex3f(10,10,0);
  glEnd(); 
   
  glutSwapBuffers();
}

void main_keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'u' : 
      break;
    case 'i' :
      break;
    case 'j' :
      break;
    case 'k' : 
      break;
    case 'n' :
      break;
    case 'm' : 
      break;
    default:
      break;
  }
  main_reshape(WIDTH, HEIGHT);
}

void idle()
{
  main_display();
}

void init(void)
{
  // do some init stuff
}
main(int argc, char** argv)
{
  std::cout << "Boom Boom!" << std::endl;
  init();
  std::cout << "made it past init" << std::endl;
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);
  glutInit(&argc, argv);

  int window = glutCreateWindow("Demo");
  glutReshapeFunc(main_reshape);
  glutDisplayFunc(main_display);
  glutKeyboardFunc(main_keyboard);
  glutIdleFunc(idle);



  glutMainLoop();

  return 0;

}
