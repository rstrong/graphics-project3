// Reaction.cpp
// reaction diffuse generation class

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ReactionDiff.h"


ReactionDiff::ReactionDiff()
{
}

void ReactionDiff::init(int type, float s)
{
  TYPE = type;
  speed = s;
}
void ReactionDiff::set_size(int x, int y)
{
  xsize = x;
  ysize = y;
}

void ReactionDiff::set_p(float a, float b, float c)
{
  p1 = a;
  p2 = b;
  p3 = c;
}

void ReactionDiff::set_diff(float a, float b)
{
  diff1 = a;
  diff2 = b;
}

void ReactionDiff::set_arand(float a)
{
  arand = a;
}

void ReactionDiff::calculate_semistable(void)
{
  int i,j;
  float ainit,binit,cinit,dinit,einit;
  ainit = 0;
  binit = 0;
  cinit = 0;
  dinit = 0;
  einit = 0;
   
  if(TYPE == 1)
  {
    for(i = 0; i < xsize; i++)
    {
      ainit = p2 / (2 * p1);
      binit = ainit;
      cinit = 0.02 * ainit * ainit * ainit / p2;
      dinit = ainit;
      einit = ainit;

      for(j = 0; j < ysize; j++)
      {
        a[i][j] = ainit;
        b[i][j] = binit;
        c[i][j] = cinit;
        d[i][j] = dinit;
        e[i][j] = einit;
        ai[i][j] = 1 + frand (-0.5 * arand, 0.5 * arand);
      }
    }
  }
  if(TYPE == 2)
  {
    // todo
  }
}

float ReactionDiff::frand(float min, float max)
{
  return ((max-min)*((float)rand()/RAND_MAX))+min;
}

void ReactionDiff::run_stripe(void)
{
  int i,j;
  int iprev,inext,jprev,jnext;
  float aval,bval,cval,dval,eval;
  float ka,kc,kd;
  float temp1,temp2;
  float dda,ddb;
  float ddd,dde;

  for(i = 0; i < xsize; i++)
  {
    ka = -p1 - 4 * diff1;
    kc = -p2;
    kd = -p3 - 4 * diff2;

    iprev = (i + xsize - 1) % xsize;
    inext = (i + 1) % xsize;
    for(j = 0; j < ysize; j++)
    {
      jprev = (j + ysize - 1) % ysize;
      jnext = (j + 1) % ysize;

      aval = a[i][j];
      bval = b[i][j];
      cval = c[i][j];
      dval = d[i][j];
      eval = e[i][j];

      temp1 = 0.01 * aval * aval * eval * ai[i][j];
      temp2 = 0.01 * bval * bval * dval;

      dda = a[i][jprev] + a[i][jnext] + a[iprev][j] + a[inext][j];
      ddb = b[i][jprev] + b[i][jnext] + b[iprev][j] + b[inext][j];
      ddd = d[i][jprev] + d[i][jnext] + d[iprev][j] + d[inext][j];
      dde = e[i][jprev] + e[i][jnext] + e[iprev][j] + e[inext][j];

      da[i][j] = aval * ka + diff1 * dda + temp1 / cval;
      db[i][j] = bval * ka + diff1 * ddb + temp2 / cval;
      dc[i][j] = cval * kc + temp1 + temp2;
      dd[i][j] = dval * kd + diff2 * ddd + p3 * aval;
      de[i][j] = eval * kd + diff2 * dde + p3 * bval;
   
    }

  }

  for (i = 0; i < xsize; i++)
  {
    for (j = 0; j < ysize; j++)
    {
      a[i][j] += (speed * da[i][j]);
      b[i][j] += (speed * db[i][j]);
      c[i][j] += (speed * dc[i][j]);
      d[i][j] += (speed * dd[i][j]);
      e[i][j] += (speed * de[i][j]);
    }
  }

}

void ReactionDiff::run(void)
{
  int k = 0;
  int iterations = 999999999;
  for(k = 0; k < iterations; k++)
  {
    if(TYPE == 1)
    {
      display(a);
      run_stripe();
    }
  }
}

void ReactionDiff::display(float values[MAX][MAX])
{
  int i,j;
  float output;
  float min =  1e20;
  float max = -1e20;

  /* find minimum and maximum values */

  for (i = 0; i < xsize; i++)
  {
    for (j = 0; j < ysize; j++) 
    {
      if (values[i][j] < min)
      {
        min = values[i][j];
      }
      if (values[i][j] > max)
      {
        max = values[i][j];
      }
    }
  }

  if (min == max) 
  {
    min = max - 1;
    max = min + 2;
  }

  
  /* display the values */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      output = (values[i][j] - min) / (max - min);
      output = output * 255.0;
      printf("WRITE PIXEL (%d,%d) value -> %d\n",i,j,(int)output);
      //writepixel (i, j, (int) output);
    }

}
