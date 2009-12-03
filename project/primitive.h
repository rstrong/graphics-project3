#include <vector>
#include <mathutil.h>
#include "noise.h"

void generateCylinder(Mesh* i)
{
  unsigned int f;
  int size;
  for(f = 0; f < 362; f+= 12)
  {
    i->m_v.push_back(Vec3f(sin(f*PI/180), 0, cos(f*PI/180)));
    i->m_t.push_back(Vec3f(((float)f/362), -0.5, 0)); 
    i->m_v.push_back(Vec3f(sin(f*PI/180), 2, cos(f*PI/180)));
    i->m_t.push_back(Vec3f(((float)f/362), 0.5, 0));
  }

  i->m_v.push_back(Vec3f(0,0,0));
  i->m_t.push_back(Vec3f(2, 2, 2));
  i->m_v.push_back(Vec3f(0,2,0));
  i->m_t.push_back(Vec3f(2, 2, 2));
  size = i->m_v.size();
  for(f = 0; f < (i->m_v.size() - 2) - 2; f += 2)
  {

    i->m_vi.push_back(f+1); i->m_ti.push_back(f+1);
    i->m_vi.push_back(f); i->m_ti.push_back(f+2);
    i->m_vi.push_back(f+2); i->m_ti.push_back(f+2);
    
    // side of i triangle two

    i->m_vi.push_back(f+1); i->m_ti.push_back(f+1);
    i->m_vi.push_back(f+2); i->m_ti.push_back(f+2);
    i->m_vi.push_back(f+3); i->m_ti.push_back(f+3);

    // top of i
    i->m_vi.push_back(f+1); i->m_ti.push_back(f+1);
    i->m_vi.push_back(f+3); i->m_ti.push_back(f+3);
    i->m_vi.push_back(i->m_v.size()-1); i->m_ti.push_back(i->m_v.size()-1);
    
   //bottom of i
    i->m_vi.push_back(f); i->m_ti.push_back(f);
    i->m_vi.push_back(f + 2); i->m_ti.push_back(f+2);
    i->m_vi.push_back(size); i->m_ti.push_back(size);
  }
  
}

void generateCube(Mesh *i)
{
  i->m_v.push_back(Vec3f(1, 1, 1));
  i->m_v.push_back(Vec3f(1, -1, 1));
  i->m_v.push_back(Vec3f(-1, 1, 1));
  i->m_v.push_back(Vec3f(-1, -1, 1));
  i->m_v.push_back(Vec3f(1, 1, -1));
  i->m_v.push_back(Vec3f(1, -1,-1));
  i->m_v.push_back(Vec3f(-1, 1, -1));
  i->m_v.push_back(Vec3f(-1, -1, -1));
  
  i->m_t.push_back(Vec3f(0,0,0));
  i->m_t.push_back(Vec3f(0,1,0));
  i->m_t.push_back(Vec3f(1,0,0));
  i->m_t.push_back(Vec3f(1,1,0));

  // triangle faces
  i->m_vi.push_back(1); i->m_vi.push_back(0); i->m_vi.push_back(2);
  i->m_vi.push_back(3); i->m_vi.push_back(1); i->m_vi.push_back(2);
  i->m_ti.push_back(1); i->m_ti.push_back(0); i->m_ti.push_back(2);
  i->m_ti.push_back(3); i->m_ti.push_back(1); i->m_ti.push_back(2);

  i->m_vi.push_back(6); i->m_vi.push_back(4); i->m_vi.push_back(5);
  i->m_vi.push_back(6); i->m_vi.push_back(5); i->m_vi.push_back(7);
  i->m_ti.push_back(2); i->m_ti.push_back(0); i->m_ti.push_back(1);
  i->m_ti.push_back(2); i->m_ti.push_back(1); i->m_ti.push_back(3);
  
  i->m_vi.push_back(4); i->m_vi.push_back(0); i->m_vi.push_back(1);
  i->m_vi.push_back(4); i->m_vi.push_back(1); i->m_vi.push_back(5);
  i->m_ti.push_back(2); i->m_ti.push_back(0); i->m_ti.push_back(1);
  i->m_ti.push_back(2); i->m_ti.push_back(1); i->m_ti.push_back(3);
  
  i->m_vi.push_back(0); i->m_vi.push_back(4); i->m_vi.push_back(6);
  i->m_vi.push_back(2); i->m_vi.push_back(0); i->m_vi.push_back(6);
  i->m_ti.push_back(1); i->m_ti.push_back(0); i->m_ti.push_back(2);
  i->m_ti.push_back(3); i->m_ti.push_back(1); i->m_ti.push_back(2);
  
  i->m_vi.push_back(2); i->m_vi.push_back(6); i->m_vi.push_back(7);
  i->m_vi.push_back(2); i->m_vi.push_back(7); i->m_vi.push_back(3);
  i->m_ti.push_back(2); i->m_ti.push_back(0); i->m_ti.push_back(1);
  i->m_ti.push_back(2); i->m_ti.push_back(1); i->m_ti.push_back(3);

  i->m_vi.push_back(7); i->m_vi.push_back(5); i->m_vi.push_back(1);
  i->m_vi.push_back(7); i->m_vi.push_back(1); i->m_vi.push_back(3);
  i->m_ti.push_back(2); i->m_ti.push_back(0); i->m_ti.push_back(1);
  i->m_ti.push_back(2); i->m_ti.push_back(1); i->m_ti.push_back(3);
}

// 0 -> flat
// 1 -> 
// 2 -> marble
void generatePlane(Mesh *i, int type)
{
  int x,y;

  for(x = -100; x < 101; x++)
  {
    for(y = -100; y < 101; y++)
    {
      if(type == 0)
      {
        i->m_v.push_back(Vec3f(x, 0, y));
        i->m_t.push_back(Vec3f(((float)(x+100)/200),((float)(y+100)/200),0));
      }
      if(type == 1)
      {
        i->m_v.push_back(Vec3f(x,(-10 * SumNoise(x,y)),y));
        i->m_t.push_back(Vec3f(((float)(x+100)/200),((float)(y+100)/200),0));
      }
      if(type == 2)
      {
        i->m_v.push_back(Vec3f(x, (-10 *MarbleNoise(x,y)),y));
        i->m_t.push_back(Vec3f(((float)(x+100)/200),((float)(y+100)/200),0));
      }
    }
  }


  for(x = 0; x < 200; x++)
  {
    for(y = 0; y < 200; y++)
    {
      i->m_vi.push_back(y + (x*200)); i->m_ti.push_back(y + (x*200));
      i->m_vi.push_back(y + (x*200) + 201); i->m_ti.push_back(y + (x*200) + 201);
      i->m_vi.push_back(y+ (x*200) + 200); i->m_ti.push_back(y+ (x*200) + 200);
      
      i->m_vi.push_back(y + (x*200) + 1); i->m_ti.push_back(y + (x*200) + 1);
      i->m_vi.push_back(y + (x*200) + 2); i->m_ti.push_back(y + (x*200) + 2);
      i->m_vi.push_back(y + (x*200) + 201); i->m_ti.push_back(y + (x*200) + 201);
    }
  }
}
