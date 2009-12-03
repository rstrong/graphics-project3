#include <vector>
#include <fstream>
#include <mathutil.h>

bool isLessCrease(Vec3f, Vec3f, int);

struct Mesh
{ 
  std::vector<Vec3f> m_v; //vertex
  std::vector<Vec3f> m_c; //color
  std::vector<int> m_vi;
  std::vector<int> m_ci;

  std::vector<Vec3f> m_t; //texture
  std::vector<int> m_ti; //texture index

  std::vector<Vec3f> m_nf; // per face normal
  std::vector<Vec3f> m_nv; // per vertex normal
};

void renderPerVertexNormals(Mesh *);
void renderPerFaceNormals(Mesh *);
Mesh* load(const char *);


void clearMesh(Mesh *t)
{
  t->m_v.clear();
  t->m_c.clear();
  t->m_vi.clear();
  t->m_ci.clear();
  t->m_t.clear();
  t->m_ti.clear();
  t->m_nf.clear();
  t->m_nv.clear();
}

int strToInt(const char* c)
{
  int i;
  if(sscanf(c, "%i", &i) == 1)
  {
    return i;
  }
  else
  {
    return 0;
  }
}


void renderObject(Mesh *t, float r,float g,float b)
{
  std::vector<Vec3f> v = t->m_v;
  std::vector<int> vi = t->m_vi;
  std::vector<Vec3f> tx = t->m_t;
  std::vector<int> ti = t->m_ti;
  std::vector<Vec3f> nv = t->m_nv;

  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for(unsigned int i = 0; i < vi.size(); i++)
  {
    glTexCoord2f(tx[ti[i]].x, tx[ti[i]].y);
    glVertex3f(v[vi[i]].x, v[vi[i]].y, v[vi[i]].z);
    glNormal3f(nv[vi[i]].x, v[vi[i]].y, v[vi[i]].z);
  }
  glEnd();

  glPushMatrix();
  if(VIS_N_FACE == 1)
  {
    glColor3f(1.0, 1.0, 1.0);
    renderPerFaceNormals(t);
  }
  if(VIS_N_VER == 1)
  {
    glColor3f(1.0, 1.0, 1.0);
    renderPerVertexNormals(t);
  }
  glPopMatrix();
}

void generatePerFaceNormals(Mesh *t)
{
  unsigned int i;
  std::vector<Vec3f> v = t->m_v;
  std::vector<int> vi = t->m_vi;

  for(i = 0; i < vi.size(); i+=3)
  {
    Vec3f ab = v[vi[i]] - v[vi[i+1]]; 
    Vec3f ac = v[vi[i]] - v[vi[i+2]];
    Vec3f temp = ab.cross(ac);
    temp = temp.normalize();
    t->m_nf.push_back(temp);
  }
}

void renderPerFaceNormals(Mesh *t)
{
  std::vector<Vec3f> v = t->m_v;
  std::vector<int> vi = t->m_vi;
  std::vector<Vec3f> n = t->m_nf;

  unsigned int i;
  int c = 0;

  for(i = 0; i < vi.size()-2; i+= 3)
  {
    float x = (((float)1/3))*(v[vi[i]].x + v[vi[i+1]].x + v[vi[i+2]].x);
    float y = (((float)1/3))*(v[vi[i]].y + v[vi[i+1]].y + v[vi[i+2]].y);
    float z = (((float)1/3))*(v[vi[i]].z + v[vi[i+1]].z + v[vi[i+2]].z);
    n[c] *= 1.5; 
    glBegin(GL_LINES);
    glVertex3f(x,y,z);
    glVertex3f(x+n[c].x, y+n[c].y, z+n[c].z);
    glEnd();
    c++;
  }
}

void renderPerVertexNormals(Mesh *t)
{
  std::vector<Vec3f> v = t->m_v;
  std::vector<int> vi = t->m_vi;
  std::vector<Vec3f> n = t->m_nv;

  unsigned int i;

  for(i = 0; i < v.size(); i++)
  {
    double x = v[i].x;
    double y = v[i].y;
    double z = v[i].z;
    n[i] *= 1.5;
    glBegin(GL_LINES);
    glVertex3f(x,y,z);
    glVertex3f(x+n[i].x, y+n[i].y, z+n[i].z);
    glEnd();
  }
}

void generatePerVertexNormals(bool weighted, Mesh *t, int cangle)
{
  std::vector<Vec3f> v = t->m_v;
  std::vector<int> vi = t->m_vi;
  std::vector<Vec3f> nf = t->m_nf;
  std::vector<Vec3f> nv;
  int size = vi.size();
  std::vector<int> v_t_membr[size]; // contains vertex -> triangle membership
  
  std::vector<double> v_t_a; // contains area of every triangle
  unsigned int i = 0;
  unsigned int j = 0;

  // traverse every triangle, building membership + area
  for(i = 0; i < vi.size(); i += 3)
  {
    v_t_membr[vi[i]].push_back(j);
    v_t_membr[vi[i+1]].push_back(j);
    v_t_membr[vi[i+2]].push_back(j);
    j++;

    Vec3f ab = v[vi[i+1]] - v[vi[i]];
    Vec3f ac = v[vi[i+2]] - v[vi[i]];
    double area = ab.cross(ac).length() / 2;
    v_t_a.push_back(area); 
  }
  
  Vec3f temp;
  for(i = 0; i < v.size(); i++)
  {
    temp.x = 0; temp.y = 0; temp.z = 0;
    for(j =0; j < v_t_membr[i].size(); j++)
    {
      if(weighted)
      {
        if(j == 0)
        {

          temp.x = temp.x + (v_t_a[i] * nf[v_t_membr[i][j]].x);
          temp.y = temp.y + (v_t_a[i] * nf[v_t_membr[i][j]].y);
          temp.z = temp.z + (v_t_a[i] * nf[v_t_membr[i][j]].z);
        }
        else
        {
          if(!isLessCrease(nf[v_t_membr[i][0]], nf[v_t_membr[i][j]],cangle))
          {
            temp.x = temp.x + (v_t_a[i] * nf[v_t_membr[i][j]].x);
            temp.y = temp.y + (v_t_a[i] * nf[v_t_membr[i][j]].y);
            temp.z = temp.z + (v_t_a[i] * nf[v_t_membr[i][j]].z);
          }
        }
      }
      else
      {
        if(j == 0)
        {
          temp = temp + nf[v_t_membr[i][j]];
        }
        else
        {
          if(!isLessCrease(nf[v_t_membr[i][0]], nf[v_t_membr[i][j]], cangle))
          {
            temp.x = temp.x + (v_t_a[i] * nf[v_t_membr[i][j]].x);
            temp.y = temp.y + (v_t_a[i] * nf[v_t_membr[i][j]].y);
            temp.z = temp.z + (v_t_a[i] * nf[v_t_membr[i][j]].z);
          }
        }
      }
    }
    temp = temp.normalize();
    t->m_nv.push_back(temp);
  }
  
}

bool isLessCrease(Vec3f a, Vec3f b, int creaseAngle)
{
  bool isLess = false;
  float dotp = a.dot(b);
  dotp = dotp / (a.length() * b.length());
  float angle = acos(dotp);
  angle = ((float)180/PI)*angle;

  if(angle < creaseAngle)
  {
    isLess = true;
  }

  return isLess;
}

Mesh* load(const char* file)
{
  std::ifstream infile(file);
  if(infile.fail())
  {
    std::cout << "Error Opening File: " << file << std::endl;
    return false;
  }

  Mesh* model = new Mesh;
  char current_line[1024];

  while(!infile.eof())
  {
    infile.getline(current_line, 1024);

    switch (current_line[0])
    {
    case 'v':
      {
        float x,y,z;
        switch(current_line[1])
        {
        case 'n':
          break;
        case 't':
          break;
        default:
          sscanf(current_line, "v %f %f %f", &x, &y, &z);
          //std::cout << "Loaded X,Y,Z: " << x << "," << y << "," << z << std::endl;
          model->m_v.push_back(Vec3f(x,y,z));
          model->m_t.push_back(Vec3f(0,0,0));
          break;
        }
      }
      break;

    case 'f':
      {
        char* match;
        match = strtok (current_line, " ");
        while(match != NULL)
        {
          std::string whole = match;
          if(match[0] != 'f')
          {
            int i = 0;
            int start = 0;
            int seen = 0;
            int data;
            while(match[i] != NULL)
            {
              if(match[i] == '/')
              {
                data = strToInt(whole.substr(start,i).c_str());
                //std::cout << "Match: " << data << std::endl;
                start = i + 1;
               if(seen == 0)
                {
                  model->m_vi.push_back(data-1);
                  model->m_ti.push_back(data-1);
                  seen++;
                }
                else
                {
                  // Texture
                }

              }
              if(match[i + 1] == NULL)
              {
                // Color
                data = strToInt(whole.substr(start,i+1).c_str());
                //std::cout << "Match: " << data << std::endl;
              }
              i++;
            }
            //std::cout << "Found Match: " << match << std::endl;
          }
          match = strtok(NULL, " ");
        }
        break;
      }
    default: break;
    }
  }
  infile.close();
  return model;
}

