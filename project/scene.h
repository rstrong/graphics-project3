
Mesh plane;
Mesh cylinder;
Mesh cube;
Mesh buggy;
Mesh elephant;

int cur_plane = -1;

void move_car(void);

void init_ground(int type)
{
  if(cur_plane != type)
  {
    clearMesh(&plane);
    generatePlane(&plane, type);
    generatePerFaceNormals(&plane);
  
    if(VIS_N_VER == 2)
    {
      generatePerVertexNormals(true, &plane, C_ANGLE);
    }
    else
    {
      generatePerVertexNormals(false, &plane, C_ANGLE);
    }
    cur_plane = type;
  }

}

void init_cylinder(void)
{
  generateCylinder(&cylinder);
  generatePerFaceNormals(&cylinder);
  generatePerVertexNormals(true, &cylinder, C_ANGLE);
}

void init_cube(void)
{
  generateCube(&cube);
  generatePerFaceNormals(&cube);
  generatePerVertexNormals(true, &cube, C_ANGLE);
}

void init_car(void)
{
  Mesh *tmp;
  tmp = load("dirtbug.obj");
  buggy = *tmp;
  generatePerFaceNormals(&buggy);
  generatePerVertexNormals(true,&buggy, C_ANGLE);
}

void init_elephant(void)
{
  Mesh *tmp;
  tmp = load("elephant.obj");
  elephant = *tmp;
  generatePerFaceNormals(&elephant);
  generatePerVertexNormals(true,&elephant, C_ANGLE);
}

void re_normalize(void)
{
  /*generatePerVertexNormals(true,&buggy, C_ANGLE);
  generatePerVertexNormals(true,&elephant, C_ANGLE);
  generatePerVertexNormals(true,&cube, C_ANGLE);
  generatePerVertexNormals(true,&plane, C_ANGLE);
  generatePerVertexNormals(true,&cylinder, C_ANGLE);*/
}

void columns(void)
{
  if(TEXTURE_OPTION > 0)
  {
    load_beech();
  }
  glPushMatrix();
  glScalef(4.0, 12.0, 4.0);
  glTranslatef(-24, 0, 24);

  renderObject(&cylinder,0.3,0.4,0.5);
  for(unsigned int i = 0; i < 5; i++)
  {
    glTranslatef(9.5, 0, 0);
    renderObject(&cylinder,0.3,0.4,0.5);
  }
  glTranslatef(-5*9.5,0,0);
  for(unsigned int i = 0; i < 5; i++)
  {
    glTranslatef(0,0,-9.5);
    renderObject(&cylinder,0.3,0.4,0.5);
  }
  for(unsigned int i = 0; i < 5; i++)
  {
    glTranslatef(9.5,0,0);
    renderObject(&cylinder,0.3,0.4,0.5);
  }
  glTranslatef(0, 0, 33);
  renderObject(&cylinder,0.3,0.4,0.5);
  glTranslatef(-19, 0, 0);
  renderObject(&cylinder,0.3,0.4,0.5);

  glTranslatef(-19,0,-13.6);
  renderObject(&cylinder,0.3,0.4,0.5);
  glTranslatef(9,0,0);
  renderObject(&cylinder,0.3,0.4,0.5);
  glTranslatef(9,0,0);
  renderObject(&cylinder,0.3,0.4,0.5);
  glTranslatef(9,0,0);
  renderObject(&cylinder,0.3,0.4,0.5);
  glPopMatrix();
}

void walls(void)
{
  if(TEXTURE_OPTION > 0)
  {
    load_stone();
  }
  glPushMatrix();
  glColor3f(0.5,0.4,0.3);
 
  // +X walls
  glScalef(16.0, 12.0, 1.0);
  glTranslatef(0.0,1.0,0.0);
  glTranslatef(4.7,0,-94);
  renderObject(&cube,0.5,0.4,0.3);
  for(unsigned int i = 0; i < 7; i++)
  {
    glTranslatef(-1.4,0,0);
    renderObject(&cube,0.5,0.4,0.3);
  }
  glTranslatef(-1.4,0,190);
  for(unsigned int i = 0; i < 8; i++)
  {
    glTranslatef(1.4,0,0);
    renderObject(&cube,0.5,0.4,0.3);
  }
  
  glTranslatef(0,0,-58);
  renderObject(&cube,0.5,0.4,0.3);
  glTranslatef(-1.2,0,0);
  renderObject(&cube,0.5,0.4,0.3);
  glTranslatef(-1.2,0,0);
  renderObject(&cube,0.5,0.4,0.3);
  glTranslatef(-0.3,0,-54);
  renderObject(&cube,0.5,0.4,0.3);
  for(unsigned int i = 0; i < 5; i++)
  {
    glTranslatef(-1.4, 0,0);
    renderObject(&cube,0.5,0.4,0.3);
  }
  glPopMatrix();

  // +Z walls
  glPushMatrix(); 
  glTranslatef(-10.7,0,-18); 
  glScalef(1.0, 12.0, 16.0);
  glTranslatef(0,1,0);
  glTranslatef(-85,0,7.5);
  for(unsigned int i = 0; i < 7; i++)
  {
    glTranslatef(0,0,-1.65);
    renderObject(&cube,0.5,0.4,0.3);
  }
  renderObject(&cube,0.5,0.4,0.3);

  glTranslatef(190,0,0.3);
  renderObject(&cube,0.5,0.4,0.3);
  for(unsigned int i = 0; i < 6; i++)
  {
    glTranslatef(0,0,1.65);
    renderObject(&cube,0.5,0.4,0.3);
  }
  glPopMatrix();
}

void ground(void)
{
  if(TEXTURE_OPTION > 0)
  {
    load_grass();
  }
  glPushMatrix();
  glColor3f(0.2,0.1,0.6);
  renderObject(&plane,0.2,0.1,0.6);

  glPopMatrix();
}

void eleph(void)
{
  glPushMatrix();
  glColor3f(0.6,0.6,0.6);
  glTranslatef(70,5,70);
  glRotated(-90,0,1,0);
  glScalef(0.05,0.05,0.05);
  renderObject(&elephant,0.3,0.6,0.3);
  glPopMatrix();
}

void car(void)
{
  if(CAMERA_OPTION != 3)
  {
    glPushMatrix();
    glColor3f(0.1, 0.4, 0.3);
    glTranslatef(carx, cary, carz);
    glTranslatef(0,5,0);
    glScalef(0.05,0.05,0.05);
    glRotated(car_angle+90,0.0, 1.0, 0.0);
    renderObject(&buggy,0.1,0.4,0.3); 
    glPopMatrix();
  }
  move_car();
}

void move_car(void)
{
  carx += steer.x;
  carz += steer.z;
}
