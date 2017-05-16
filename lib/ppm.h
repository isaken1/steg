#ifndef _PPM_H_
#define _PPM_H_

#include <stdio.h>
#include <stdlib.h>

  typedef struct {
    unsigned char red, green, blue;
  } PPM_Pixel;

  typedef struct {
    int height, width, rgb_component;
    PPM_Pixel *pixels;
  } PPM_Image;

  PPM_Image* load_P6_PPM (const char *file_name);

  void check_PPM_Format (FILE *file, char *file_name);

#endif
