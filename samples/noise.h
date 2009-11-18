#include <math.h>
#include "PerlinNoise.h"
ImprovedNoise noise;

double  PlainNoise(int x, int y)
{
  double scale = 0.05;
  double n;

  n = noise.noise(x * scale , y * scale, 11.5);

  return n;
}

// Will return value between -1 and 0
double SumNoise(int x, int y)
{
  // always use 7 band 
  double scale = 0.03;
  double n = 0;
  double amp = 2;
  for(int i = 1; i < 8; i++)
  {
    n += (pow(amp, -i)) * noise.noise(x*(pow(scale, i)), y*(pow(scale,i)), 11.5);
  }
  n = n - 0.4;
  return n;
}

// will return value between -1 and 0
double MarbleNoise(int x, int y)
{
  double scale = 0.03;
  double n;
  double amp = 2;
  for(int i = 1; i < 5; i++)
  {
    n += (pow(amp, -i)) * noise.noise(x*(pow(scale, i)), y*(pow(scale,i)), 11.5);
  }
  n = sin((double)n);
  n = n/1.8;
  n = n - 0.3;

  return n;
}
