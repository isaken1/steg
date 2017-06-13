#ifndef _BMP_H_
#define _BMP_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  uint16_t type;
  uint32_t fileSize;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
} BMP_File_Header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  uint32_t bSize;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bitCount;
  uint32_t compression;
  uint32_t imageSize;
  int32_t xPixelsPerMeter;
  int32_t yPixelsPerMeter;
  uint32_t colorUsed;
  uint32_t importantColor;
} BMP_Info_Header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  BMP_File_Header fileHeader;
  BMP_Info_Header infoHeader;
  unsigned char *imageData;
} BMP_File;
#pragma pack(pop)

BMP_File loadBMP(const char *filename);
void writeBMP(BMP_File image, unsigned char *data);

#endif
