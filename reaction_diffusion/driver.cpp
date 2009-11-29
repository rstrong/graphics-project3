#include <iostream>
#include "ReactionDiff.h"

int main()
{
  ReactionDiff rd;
  std::cout << "Got reaction-diff object..." << std::endl;
  rd.init(1,1.0);
  rd.set_size(200,200);
  rd.set_p(0.04,0.06,0.04);
  rd.set_diff(0.009,0.2);
  rd.set_arand(0.02);

  rd.run();

  return 1;
}
