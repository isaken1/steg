#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./lib/ppm.h"
#include "./lib/bmp.h"

int main(int argc, char **argv);
void encodePPM(const char *text_file, const char *output_file);
void encodeBMP(const char *host_file);
void decode();
void run();

//Encode flag
int e_flag = 0;
//Decode flag
int d_flag = 0;
//Input file
char *i_value = NULL;
//Image format
char *f_value = NULL;
//Host image
char *h_value = NULL;

#endif
