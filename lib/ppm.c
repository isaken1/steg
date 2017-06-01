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
  image->data = (PPM_Pixel *) malloc(image->width * image->height * sizeof(PPM_Pixel));
  if (!image) {
    fprintf(stderr, "Failed to allocate memory.\n");
    exit(1);
  }

  c = (fread(image->data, 3 * image->width, image->height, file));

  if (c != image->height) {
    fprintf(stderr, "Failed to load image.\n");
    exit(1);
  }

  //--------------------FINISHED READING IMAGE DATA--------------------------//

  //close the file
  fclose(file);
  return (image);
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

void write_P6_PPM(const char *file_name, PPM_Image *image) {
  FILE *fp;
  fp.open(file_name, "wb");

  if (!fp) {
    fprintf(stderr, "Unable to create/open file '%s'.", file_name);
    exit(1);
  }

  //-----------------------WRITE THE HEADER------------------------
  //Format
  fprintf(fp, "P6\n");

  //comments
  fprintf(fp, "# Image created by the Project Steg (Illuminatti).\n");

  //size
  fprintf(fp, "%d %d\n", image->width, image->height);

  //RGB component
  fprintf(fp, "%d\n", image->rgb_component);

  fwrite(image->data, 3 * image->width, image->height, fp);
  fclose(fp);
}








// Take the least significant bytes and change them according to the message
// 1 char = 1 byte. 1 int = 4 bytes
// Which means 1 char needs 8 least significant bytes to be written in, which means 2 integers variables.
