#ifndef _MAIN_H_
#define _MAIN_H_

int main(int argc, char **argv);
void encode(const char *file_name, const char *output_file);
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
