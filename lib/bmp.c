#include "bmp.h"


BMP_File loadBMP(const char *file_name) {
  FILE *file;
  BMP_File_Header fileHeader;
  BMP_Info_Header infoHeader;
  BMP_File image;
  unsigned char *bmpData;

  printf("Got here1!\n");

  //Open the file
  file = fopen(file_name, "rb");
  if (!file) {
    fprintf(stderr, "Failed to read file %s.\n", file_name);
    exit(1);
  }

  printf("Got here2!\n");
  //Read the file header
  fread(&fileHeader, sizeof(BMP_File_Header), 1, file);

  printf("Got here3!\n");

  //Check format
  if (fileHeader.type != 0x4D42) {
    fclose(file);
    fprintf(stderr, "Invalid image");
    exit(1);
  }

  printf("Got here4!\n");

  //Read the info header
  fread(&infoHeader, sizeof(BMP_Info_Header), 1, file);

  printf("Got here5!\n");

  //-------------------------Checking the image--------------------------
  if (infoHeader.bSize != 40) {
    fclose(file);
    fprintf(stderr, "Couldn't load image correctly");
    exit(1);
  }

  printf("Got here6!\n");

  if ((infoHeader.planes != 1) || (infoHeader.bitCount != 24)) {
    fclose(file);
    fprintf(stderr, "Invalid image");
    exit(1);
  }

  printf("Got here7!\n");

  if (infoHeader.compression != 0) {
    fclose(file);
    fprintf(stderr, "This software currently does not support compressed BMP files");
    exit(1);
  }

  printf("Got here8!\n");

  //Move the file through the offset until the beginning of the data itself
  fseek(file, fileHeader.offset, SEEK_SET);

  printf("Got here9!\n");

  //Allocate the char array to the needed size to hold the data
  bmpData = (unsigned char *) malloc(infoHeader.bSize);

  printf("Got here10!\n");

  //Actually read the image data
  fread(bmpData, infoHeader.bSize, 1, file);

  printf("Got here11!\n");

  //Verify the data
  if (!bmpData) {
    fclose(file);
    fprintf(stderr, "Couldn't load image data correctly");
    exit(1);
  }

  printf("Got here12!\n");

  image.fileHeader = fileHeader;

  printf("Got here13!\n");
  image.infoHeader = infoHeader;
  printf("Got here14!\n");
  image.imageData = bmpData;
  printf("Got here15!\n");

  fclose(file);
  return image;

}

void writeBMP(){

}
