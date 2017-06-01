#ifndef _PPM_H_
#define _PPM_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
  unsigned char red, green, blue;
} PPM_Pixel;

typedef struct {
  int height, width, rgb_component;
  PPM_Pixel *data;
} PPM_Image;

PPM_Image* load_P6_PPM(const char *file_name);
void check_PPM_Format (FILE *file, const char *file_name);
void write_P6_PPM(PPM_Image* image);

#endif
