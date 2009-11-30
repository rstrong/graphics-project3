#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>

// The beginnings of ours...
#include <ReactionDiff.h>


int WIDTH = 640;
int HEIGHT = 480;
ReactionDiff rd;
int iter = 0;

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
  iter++;
  if(iter % 1000 == 0)
  {
    std::cout << "iteration " << iter << std::endl;
  }
  rd.run();
  float mn,mx,output;
  int i,j;
  mn = rd.get_min();
  mx = rd.get_max();
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(1.0f);
  glBegin(GL_POINTS);
  for (i = 0; i < 200; i++)
  {
    for (j = 0; j < 200; j++)
    {
      output = (rd.get(i,j) - mn) / (mx - mn);
      output = output * 255.0;
      glColor3ub((int)output,0,0);
      glVertex3f(i,j,0);
    }
  }
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
  rd.init(1,1.0);
  rd.set_size(200,200);
  rd.set_p(0.04,0.06,0.04);
  rd.set_diff(0.009,0.2);
  rd.set_arand(0.02);
  rd.calculate_semistable();
}
main(int argc, char** argv)
{
  rd.init(1,1.0);
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
