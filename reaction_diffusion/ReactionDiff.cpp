// Reaction.cpp
// reaction diffuse generation class

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "ReactionDiff.h"


ReactionDiff::ReactionDiff()
{
}

void ReactionDiff::init(int type, float s)
{
  TYPE = type;
  speed = s;
}

void ReactionDiff::set_binit(float in)
{
  beta_init = in;
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
    for (i = 0; i < xsize; i++)
    {
      for (j = 0; j < ysize; j++) 
      {
        a[i][j] = 4;
        b[i][j] = 4;
        c[i][j] = beta_init + frand (-beta_rand, beta_rand);
      }
    }
  }
}

void ReactionDiff::set_brand(float in)
{
  beta_rand = in;
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

void ReactionDiff::run_spot(void)
{
  int i,j;
  int iprev,inext,jprev,jnext;
  float aval,bval;
  float ka;
  float dda,ddb;
  float Diff1,Diff2;

  Diff1 = diff1 / 2.0;
  Diff2 = diff2 / 2.0;
  ka = p1 / 16.0;

  for (i = 0; i < xsize; i++) 
  {
    iprev = (i + xsize - 1) % xsize;
    inext = (i + 1) % xsize;

    for (j = 0; j < ysize; j++) 
    {
      jprev = (j + ysize - 1) % ysize;
      jnext = (j + 1) % ysize;

      aval = a[i][j];
      bval = b[i][j];

      dda = a[i][jprev] + a[i][jnext] + a[iprev][j] + a[inext][j] - 4 * aval;
      ddb = b[i][jprev] + b[i][jnext] + b[iprev][j] + b[inext][j] - 4 * bval;

      da[i][j] = ka * (16 - aval * bval) + Diff1 * dda;
      db[i][j] = ka * (aval * bval - bval - c[i][j]) + Diff2 * ddb;
    }
  }

  for (i = 0; i < xsize; i++)
  {
    for (j = 0; j < ysize; j++) 
    {
      a[i][j] += (speed * da[i][j]);
      b[i][j] += (speed * db[i][j]);
      if (b[i][j] < 0)
      {
        b[i][j] = 0;
      }
    }
  }
}

void ReactionDiff::run(void)
{
  if(TYPE == 1)
  {
    run_stripe();
    update_min_max(a);
  }
  if(TYPE == 2)
  {
    run_spot();
    update_min_max(b);
  }
}

float ReactionDiff::get_min(void)
{
  return min;
}

float ReactionDiff::get_max(void)
{
  return max;
}

void ReactionDiff::update_min_max(float values[MAX][MAX])
{
  int i,j;
  float output;
  float mn =  1e20;
  float mx = -1e20;

  /* find minimum and maximum values */

  for (i = 0; i < xsize; i++)
  {
    for (j = 0; j < ysize; j++) 
    {
      if (values[i][j] < mn)
      {
        mn = values[i][j];
      }
      if (values[i][j] > mx)
      {
        mx = values[i][j];
      }
    }
  }

  if (mn == mx) 
  {
    mn = mx - 1;
    mx = mn + 2;
  }
  min = mn;
  max = mx;
}

float ReactionDiff::get(int i,int j)
{
  if(TYPE == 1)
  {
    return a[i][j];
  }
  if(TYPE == 2)
  {
    return b[i][j];
  }
}
