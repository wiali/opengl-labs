#ifndef _LOADBMP_H
#define _LOADBMP_H


typedef struct _IMAGE
  {
  int width;
  int height;
  unsigned char* data;
  } IMAGE;

int LoadBMP(const char* file, IMAGE* out_img);

#endif
