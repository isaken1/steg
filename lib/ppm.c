#include "ppm.h"

PPM_Image* load_P6_PPM (const char *file_name){
  FILE *file;
  PPM_Image *image;
  int commentary;

  //Initialize and open the file for reading
  file = fopen(file_name, "rb");
  if (!file) {
    fprintf(stderr, "Failed to read file %s.\n", file_name);
    exit(1);
  }

  //---------------------STARTED READING IMAGE HEADER--------------------------//
  check_PPM_Format(file, file_name);

  //Skip second line commentaries, if they exist
  c = getc(file);
  while (c == '#') {
    while (getc(file) != '\n') {
      c = getc(file);
    }
  }
  ungetc(c, fp);

  //Allocate memory
  image = (PPM_Image *) malloc(sizeof(PPM_Image));
  if (!image){
    fprintf(stderr, "Failed to allocate memory space.\n");
    exit(1);
  }

  //Read image size
  c = fscanf(file, "%d %d", &image->width, &image->height);
  if (c != 2) {
    fprintf(stderr, "Failed to read image size.");
  }

  //Read PPM image RGB component
  c = fscanf(file, "%d", &image->rgb_component);
  if (c != 1) {
    fprintf(stderr, "Failed to read image RGB component.");
  }

  //----------------FINISHED READING THE IMAGE HEADER------------------------//
  //--------------------STARTED READING IMAGE DATA---------------------------//

  while (fgetc(file) != '\n');
  
  //Allocate memory for the image data inside the PPM_Image variable
  image->data = (PPM_Pixel *) malloc(img->x * img->y * sizeof(PPM_Pixel));

  if (!image) {
    fprintf(stderr, "Failed to allocate memory.\n");
    exit(1);
  }



  c = (fread(img->data,))


}

void check_PPM_Format(FILE *file, char *file_name){
  char header[16];
  if (!fgets(header, sizeof(header), file)) {
    perror(file_name);
    exit(1)
  }
  //Check if the image header is = P6
  if (header[0] != 'P' || header[1] != '6') {
    fprintf(stderr, "Invalid format.\n", );
    exit(1);
  }
}
