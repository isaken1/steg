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

PPM_Image* loadP6PPM(const char *file_name);
void checkPPMFormat (FILE *file, const char *file_name);
void writeP6PPM(PPM_Image* image);
PPM_Image* writeMessage(char *file_name, PPM_Image *image);
char* convertFileToText(FILE* file);

#endif
