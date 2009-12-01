#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>

// The beginnings of ours...
#include <ReactionDiff.h>
#include <driver.h>
#include <menu.h>

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
  if(iter % 100 == 0)
  {
    std::cout << "iteration " << iter << std::endl;
  }
  if(MODE < 2)
  {
    for(unsigned int f = 0; f < N; f++)
    {
      iter++;
      rd.run();
    }
  }

  float mn,mx,output;
  int i,j;
  mn = rd.get_min();
  mx = rd.get_max();
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0f);
  glBegin(GL_POINTS);
  for (i = 0; i < 200; i++)
  {
    for (j = 0; j < 200; j++)
    {
      output = (rd.get(i,j) - mn) / (mx - mn);
      output = output * 255.0;
      glColor3ub(0,0,(int)output);
      glVertex3f((i*2+1),(j*2+1),0);
    }
  }
  glEnd();
  glutSwapBuffers();

}

void special_keyboard(int key, int x, int y)
{
  switch(key)
  {
  default:
    break;
  }
}
void main_keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'q' : 
      dp1 += 0.01;
      std::cout << "p1 is now " << dp1 << std::endl;
      break;
    case 'Q' : 
      dp1 -= 0.01;
      std::cout << "p1 is now " << dp1 << std::endl;
      break;
    case 'w' : 
      dp2 += 0.01;
      std::cout << "p2 is now " << dp2 << std::endl;
      break;
    case 'W' : 
      dp2 -= 0.01;
      std::cout << "p2 is now " << dp2 << std::endl;
      break;
    case 'e' : 
      dp3 += 0.01;
      std::cout << "p3 is now " << dp3 << std::endl;
      break;
    case 'E' : 
      dp3 -= 0.01;
      std::cout << "p3 is now " << dp3 << std::endl;
      break;
    case 'r' :
      df1 += 0.001;
      std::cout << "diff1 is now " << df1 << std::endl;
      break;
    case 'R' :
      df1 -= 0.001;
      std::cout << "diff1 is now " << df1 << std::endl;
      break;
    case 't' :
      df2 += 0.01;
      std::cout << "diff2 is now " << df2 << std::endl;
      break;
    case 'T' :
      df2 -= 0.01;
      std::cout << "diff2 is now " << df2 << std::endl;
      break;
    case 32 :
      if(MODE == 2)
      {
        std::cout << "iterating via spacebar" << std::endl;
        rd.run();
        iter++;
      }
    default:
      break;
  }
  rd.set_p(dp1,dp2,dp3);
  rd.set_diff(df1,df2);
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
  rd.set_p(dp1,dp2,dp3);
  rd.set_diff(df1,df2);
  rd.set_arand(0.02);
  rd.calculate_semistable();
}
main(int argc, char** argv)
{
  rd.init(1,1.0);
  init();
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);
  glutInit(&argc, argv);

  int window = glutCreateWindow("Reaction Diffusion");
  glutReshapeFunc(main_reshape);
  glutDisplayFunc(main_display);
  glutKeyboardFunc(main_keyboard);
  glutIdleFunc(idle);
  setup_menus();
  glutKeyboardFunc(main_keyboard);
  glutSpecialFunc(special_keyboard);

  glutMainLoop();

  return 0;

}
