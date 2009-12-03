#include <GL/glut.h>
#include "bitmap.h"

BITMAPINFO *BitmapInfo1; /* Bitmap information */
GLubyte    *BitmapBits1; /* Bitmap data */
GLuint TexObj1;

void load_grass(void)
{
  BitmapBits1 = LoadDIBitmap("./grass.bmp", &BitmapInfo1);

  glGenTextures(1, &TexObj1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, TexObj1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // must set to 1 for compact data
  if(MAG_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  if(MAG_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  if(MINI_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  if(MINI_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }
  glTexImage2D(GL_TEXTURE_2D,
    0,                // mipmap level
    GL_RGB,             // internal format
    BitmapInfo1->bmiHeader.biWidth,  // width
    BitmapInfo1->bmiHeader.biHeight, // height
    0,                // border
    GL_BGR_EXT,           // data format  (NOTE: Bitmap's format is BGR!!!!)
    GL_UNSIGNED_BYTE,       // element per pixel
    BitmapBits1);          // data

  if(TEXTURE_OPTION == 1)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  }
  if(TEXTURE_OPTION == 2)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  }
}

BITMAPINFO *BitmapInfo2; /* Bitmap information */
GLubyte    *BitmapBits2; /* Bitmap data */
GLuint TexObj2;

void load_stone(void)
{
  BitmapBits2 = LoadDIBitmap("./rock.bmp", &BitmapInfo2);

  glGenTextures(1, &TexObj2);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, TexObj2);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // must set to 1 for compact data
  if(MAG_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  if(MAG_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  if(MINI_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  if(MINI_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }
  glTexImage2D(GL_TEXTURE_2D,
    0,                // mipmap level
    GL_RGB,             // internal format
    BitmapInfo2->bmiHeader.biWidth,  // width
    BitmapInfo2->bmiHeader.biHeight, // height
    0,                // border
    GL_BGR_EXT,           // data format  (NOTE: Bitmap's format is BGR!!!!)
    GL_UNSIGNED_BYTE,       // element per pixel
    BitmapBits2);          // data

  if(TEXTURE_OPTION == 1)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  }
  if(TEXTURE_OPTION == 2)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  }
}

BITMAPINFO *BitmapInfo3; /* Bitmap information */
GLubyte    *BitmapBits3; /* Bitmap data */
GLuint TexObj3;

void load_beech(void)
{
  BitmapBits3 = LoadDIBitmap("./beech.bmp", &BitmapInfo3);

  glGenTextures(1, &TexObj3);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, TexObj3);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // must set to 1 for compact data
  if(MAG_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  if(MAG_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  if(MINI_OPTION == 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  if(MINI_OPTION == 1)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }
  glTexImage2D(GL_TEXTURE_2D,
    0,                // mipmap level
    GL_RGB,             // internal format
    BitmapInfo3->bmiHeader.biWidth,  // width
    BitmapInfo3->bmiHeader.biHeight, // height
    0,                // border
    GL_BGR_EXT,           // data format  (NOTE: Bitmap's format is BGR!!!!)
    GL_UNSIGNED_BYTE,       // element per pixel
    BitmapBits3);          // data

  if(TEXTURE_OPTION == 1)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  }
  if(TEXTURE_OPTION == 2)
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  }
}



