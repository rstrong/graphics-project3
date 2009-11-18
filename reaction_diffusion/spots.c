/*

Make spots and stripes with reaction-diffusion.

The spot-formation system is described in the article:

  "A Model for Generating Aspects of Zebra and Other Mammailian
   Coat Patterns"
  Jonathan B. L. Bard
  Journal of Theoretical Biology, Vol. 93, No. 2, pp. 363-385
  (November 1981)

The stripe-formation system is described in the book:

  Models of Biological Pattern Formation
  Hans Meinhardt
  Academic Press, 1982


Permission is granted to modify and/or distribute this program so long
as the program is distributed free of charge and this header is retained
as part of the program.

Copyright (c) Greg Turk, 1991

*/

#include <stdio.h>
#include <math.h>

extern double atof();
extern double drand48();

float frand();

/* screen stuff */

int xsize = 30;
int ysize = 30;
int psize = 4;

/* simulation variables */

int interval = 200;
int value_switch = 1;
int stripe_flag = 0;

#define  STRIPES  1
#define  SPOTS    2

#define MAX 200

float a[MAX][MAX];
float b[MAX][MAX];
float c[MAX][MAX];
float d[MAX][MAX];
float e[MAX][MAX];

float da[MAX][MAX];
float db[MAX][MAX];
float dc[MAX][MAX];
float dd[MAX][MAX];
float de[MAX][MAX];

float ai[MAX][MAX];

float p1,p2,p3;

float diff1,diff2;

float arand;
float a_steady;
float b_steady;

float beta_init;
float beta_rand;

float speed = 1.0;

int sim = 1;


/******************************************************************************
Main routine.
******************************************************************************/

main (argc,argv)
  int  argc;
  char *argv[];
{
  char *s;

  /* parse the command line options */

  while(--argc >0 && (*++argv)[0]=='-') {
    for(s = argv[0]+1; *s; s++)
      switch(*s) {
	case 'n':
	  xsize = atoi (*++argv);
	  ysize = atoi (*++argv);
          if (xsize > MAX || ysize > MAX)
            printf ("oops, too large a screen size\n");
	  argc -= 2;
	  break;
	case 'x':
	  stripe_flag = 1;
	  break;
	default:
	  break;
      }
  }

  /* setup graphics */

/*  init_graphics (psize * xsize, psize * ysize, 40);
  set_pixel_size (psize);*/

  /* make spots or stripes */

  if (stripe_flag)
    do_stripes();
  else
    do_spots();
}


/******************************************************************************
Run Meinhardt's stripe-formation system.
******************************************************************************/

do_stripes()
{
  p1 = 0.04;
  p2 = 0.06;
  p3 = 0.04;

  diff1 = 0.009;
  diff2 = 0.2;

  arand = 0.02;

  sim = STRIPES;
  value_switch = 1;
  compute();
}


/******************************************************************************
Run Turing reaction-diffusion system.
******************************************************************************/

do_spots()
{
  beta_init = 12;
  beta_rand = 0.1;

  a_steady = 4;
  b_steady = 4;

  diff1 = 0.25;
  diff2 = 0.0625;

  p1 = 0.2;
  p2 = 0.0;
  p3 = 0.0;

  sim = SPOTS;
  value_switch = 2;
  compute();
}


/******************************************************************************
Diffuse and react.
******************************************************************************/

compute()
{
  int k;
  int iterations = 99999999;

  /* calculate semistable equilibria */

  semi_equilibria();

  /* start things diffusing */

  for (k = 0; k < iterations; k++) {

    if (k % interval == 0) {
      printf ("iteration %d\n", k);
      switch (value_switch) {
	case 1:
	  show(a);
	  break;
	case 2:
	  show(b);
	  break;
	case 3:
	  show(c);
	  break;
	case 4:
	  show(d);
	  break;
	case 5:
	  show(e);
	  break;
	default:
	  printf ("bad switch in compute: %d\n", value_switch);
	  break;
      }
    }

    /* perform reaction and diffusion */

    switch (sim) {
      case STRIPES:
	multiplicative_help();
	break;
      case SPOTS:
	turing();
	break;
      default: break;
    }
  }
}


/******************************************************************************
Create stripes with what Hans Meinhardt calls a two-species balance.
******************************************************************************/

multiplicative_help()
{
  int i,j;
  int iprev,inext,jprev,jnext;
  float aval,bval,cval,dval,eval;
  float ka,kc,kd;
  float temp1,temp2;
  float dda,ddb;
  float ddd,dde;

  /* compute change in each cell */

  for (i = 0; i < xsize; i++) {

    ka = -p1 - 4 * diff1;
    kc = -p2;
    kd = -p3 - 4 * diff2;

    iprev = (i + xsize - 1) % xsize;
    inext = (i + 1) % xsize;

    for (j = 0; j < ysize; j++) {

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

  /* affect change */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      a[i][j] += (speed * da[i][j]);
      b[i][j] += (speed * db[i][j]);
      c[i][j] += (speed * dc[i][j]);
      d[i][j] += (speed * dd[i][j]);
      e[i][j] += (speed * de[i][j]);
    }
}


/******************************************************************************
Turing's reaction-diffusion equations.
******************************************************************************/

turing()
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

  /* compute change in each cell */

  for (i = 0; i < xsize; i++) {

    iprev = (i + xsize - 1) % xsize;
    inext = (i + 1) % xsize;

    for (j = 0; j < ysize; j++) {

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

  /* affect change */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      a[i][j] += (speed * da[i][j]);
      b[i][j] += (speed * db[i][j]);
      if (b[i][j] < 0)
	b[i][j] = 0;
    }
}


/******************************************************************************
Calculate semi-stable equilibria.
******************************************************************************/

semi_equilibria()
{
  int i,j;
  float ainit,binit;
  float cinit,dinit,einit;

  ainit = binit = cinit = dinit = einit = 0;

  /* figure the values */

  switch (sim) {

    case STRIPES:
      for (i = 0; i < xsize; i++) {

	ainit = p2 / (2 * p1);
	binit = ainit;
	cinit = 0.02 * ainit * ainit * ainit / p2;
	dinit = ainit;
	einit = ainit;
	
	for (j = 0; j < ysize; j++) {
	  a[i][j] = ainit;
	  b[i][j] = binit;
	  c[i][j] = cinit;
	  d[i][j] = dinit;
	  e[i][j] = einit;
	  ai[i][j] = 1 + frand (-0.5 * arand, 0.5 * arand);
	}
      }
      break;

    case SPOTS:
      for (i = 0; i < xsize; i++)
	for (j = 0; j < ysize; j++) {
	  a[i][j] = a_steady;
	  b[i][j] = b_steady;
	  c[i][j] = beta_init + frand (-beta_rand, beta_rand);
	}
      break;

    default:
      printf ("bad case in semi_equilibria\n");
      break;
  }
}


/******************************************************************************
Switch for picking array to rescale.
******************************************************************************/

do_rescale (index,min,max)
  int index;
  float min,max;
{
  switch (index) {
    case 1:
      rescale_values (a, min, max);
      break;
    case 2:
      rescale_values (b, min, max);
      break;
    case 3:
      rescale_values (c, min, max);
      break;
    case 4:
      rescale_values (d, min, max);
      break;
    case 5:
      rescale_values (e, min, max);
      break;
    default:
      printf ("bad switch in do_rescale: %d\n", index);
      break;
  }
}


/******************************************************************************
Rescale values in array.

Entry:
  values    - array to rescale
  min_final - minimum value to map to
  max_final - maximum value to map to
******************************************************************************/

rescale_values (values,min_final,max_final)
  float values[MAX][MAX];
  float min_final;
  float max_final;
{
  int i,j;
  float val;
  float min =  1e20;
  float max = -1e20;

  /* find minimum and maximum values */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      if (values[i][j] < min)
	min = values[i][j];
      if (values[i][j] > max)
	max = values[i][j];
    }

  if (min == max) {
    min = max - .001;
    max = min + .002;
  }

  /* rescale the values */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      val = (values[i][j] - min) / (max - min);
      val = min_final + val * (max_final - min_final);
      values[i][j] = val;
    }
}


/******************************************************************************
Display the activator.
******************************************************************************/

show(values)
  float values[MAX][MAX];
{
  int i,j;
  float output;
  float min =  1e20;
  float max = -1e20;

  /* find minimum and maximum values */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      if (values[i][j] < min)
	min = values[i][j];
      if (values[i][j] > max)
	max = values[i][j];
    }

  if (min == max) {
    min = max - 1;
    max = min + 2;
  }

  printf ("min max diff: %f %f %f\n", min, max, max - min);

  /* display the values */

  for (i = 0; i < xsize; i++)
    for (j = 0; j < ysize; j++) {
      output = (values[i][j] - min) / (max - min);
      output = output * 255.0;
      printf("WRITE PIXEL (%d,%d) value -> %d\n",i,j,(int)output);
      //writepixel (i, j, (int) output);
    }

  //flushbuffers();
}


/******************************************************************************
Pick a random number between min and max.
******************************************************************************/

float frand(min, max)
  float min,max;
{
  return (min + drand48() * (max - min));
}

