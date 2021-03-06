#include "ppm.h"

PPM_Image* loadP6PPM (const char *file_name){
  FILE *file;
  PPM_Image *image;
  int c;

  //Initialize and open the file for reading
  file = fopen(file_name, "rb");
  if (!file) {
    fprintf(stderr, "Failed to read file %s.\n", file_name);
    exit(1);
  }

  //---------------------STARTED READING IMAGE HEADER--------------------------//
  checkPPMFormat(file, file_name);

  //Skip second line commentaries, if they exist
  c = getc(file);
  while (c == '#') {
    while (getc(file) != '\n') {
      c = getc(file);
    }
  }
  ungetc(c, file);

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

void checkPPMFormat(FILE *file, const char *file_name){
  char header[16];
  if (!fgets(header, sizeof(header), file)) {
    perror(file_name);
    exit(1);
  }

  //Check if the image header is = P6
  if (header[0] != 'P' || header[1] != '6') {
    fprintf(stderr, "Invalid format.\n");
    exit(1);
  }
}

void writeP6PPM(PPM_Image *image) {
  FILE *fp;
  fp = fopen("output.ppm", "wb");

  if (!fp) {
    fprintf(stderr, "Unable to create output file");
    exit(1);
  }

  //-----------------------WRITE THE HEADER------------------------
  //Format
  fprintf(fp, "P6\n");

  //comments
  fprintf(fp, "# Image created through the Project Steg (Illuminatti).\n");

  //size
  fprintf(fp, "%d %d\n", image->width, image->height);

  //RGB component
  fprintf(fp, "%d\n", image->rgb_component);

  fwrite(image->data, 3 * image->width, image->height, fp);
  fclose(fp);
}

char *convertFileToText(FILE *file) {
  long size;
  char *buffer;

  //Get file size
  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  rewind(file);

  //Alloc memory to the buffer
  buffer = calloc(1, size + 1);
  if (!buffer) {
    fclose(file);
    fprintf(stderr, "Unable to allocate memory");
    exit(1);
  }

  //Read file
  if (fread(buffer, size, 1, file) != 1) {
    fclose(file);
    free(buffer);
    fprintf(stderr, "Unable to read file.");
    exit(1);
  }

  fclose(file);
  return buffer;
}

PPM_Image* writeMessage(char *file_name, PPM_Image *image) {
  FILE *input = fopen(file_name, "r");
  if (!input) {
    fprintf(stderr, "Unable to read file.");
    exit(1);
  }

  char *message = convertFileToText(input);
  char *message_bits;

  int i, j;
  //Get the bit amount in the message
  int string_bits_count = strlen(message) * sizeof(char) * 8;
  printf("String bits count: %d\n", string_bits_count);
  int counter = 0;

  //Alloc the array that will hold the message's bits
  message_bits = malloc(string_bits_count);

  if (image) {

    int image_size = 3 * image->height * image->width;
    printf("Image size: %d\n", image_size);

    //Check if image will hold the entire message plus the escape character
    if ((strlen(message) + sizeof(char)) * sizeof(char) > image_size * sizeof(char)) {
      fprintf(stderr, "Message too long for the selected image");
      exit(1);
    } else {
      //Set the message bits in the array, note that the array holds the
      //inverted message
      while (counter < string_bits_count) {
        *(message_bits + counter) = ((*message) % 2);
        //printf("Counter: %d\n", counter);
        *message = *message >> 1;
        //printf("Message bit: %c\n", *(message_bits + counter));
        counter++;
      }

      int bit_index = 0;

      for (i = 0; i < string_bits_count; i++) {
        if (*(message_bits + bit_index) != (image->data[i].red % 2)) {
          //printf("Original data: %d\n", image->data[i].red);
          image->data[i].red = (image->data[i].red & 0xFE) | *(message_bits + bit_index);
          //printf("New data: %d\n", image->data[i].red);
        }
        bit_index++;

        if (*(message_bits + bit_index) != (image->data[i].green % 2)) {
          image->data[i].green = (image->data[i].green & 0xFE) | *(message_bits + bit_index);
        }
        bit_index++;

        if (*(message_bits + bit_index) != (image->data[i].blue % 2)) {
          image->data[i].blue = (image->data[i].blue & 0xFE) | *(message_bits + bit_index);
        }
        bit_index++;
      }


      int escape_index = 0;
      char escape_char = '\0';

      //Insert the escape character after the message insert.
      if (escape_char % 2 != (image->data[i].red % 2)) {
        image->data[i].red = (image->data[i].red & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      if (escape_char % 2 != (image->data[i].green % 2)) {
        image->data[i].green = (image->data[i].green & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      if (escape_char % 2 != (image->data[i].blue % 2)) {
        image->data[i].blue = (image->data[i].blue & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      i++;
      if (escape_char % 2 != (image->data[i].red % 2)) {
        image->data[i].red = (image->data[i].red & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      if (escape_char % 2 != (image->data[i].green % 2)) {
        image->data[i].green = (image->data[i].green & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      if (escape_char % 2 != (image->data[i].blue % 2)) {
        image->data[i].blue = (image->data[i].blue & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      i++;
      if (escape_char % 2 != (image->data[i].red % 2)) {
        image->data[i].red = (image->data[i].red & 0xFE) | escape_char % 2;
      }
      escape_char = escape_char >> 1;
      if (escape_char % 2 != (image->data[i].green % 2)) {
        image->data[i].green = (image->data[i].green & 0xFE) | escape_char % 2;
      }
    }
  }

  return image;
}


// Take the least significant bytes and change them according to the message
// 1 char = 1 byte. 1 int = 4 bytes
// Which means 1 char needs 8 least significant bits to be written in, which means 2 integers variables.
