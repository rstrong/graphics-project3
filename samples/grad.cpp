#include "noise.h"
#include <iostream> 

int main(void)
{
  int i,j;
  double n;

  for(i = 0; i < 100; i++)
  {
    for(j = 0; j < 100; j++)
    {
      n = SumNoise(i,j);
      std::cout << i << "," << j << " => " << n << std::endl;

    }
  }


  return 1;
}
