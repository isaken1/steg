#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "./lib/ppm.h"
#include "main.h"

void encode(const char *file_name, const char *output_file, const char *file_format) {
	write_P6_PPM(load_P6_PPM(file_name), "./output/output.ppm");
}

void decode() {
	//TODO
}

void run() {
	if (e_flag == 1) {
		encode(i_value, h_value, f_value);
	} else if (d_flag == 1) {
		decode();
	}
}

int main(int argc, char **argv) {
	int index;
	int c;

	int opterr = 0;


	while (index < argc) {
		if ((c = getopt (argc, argv, "edi:f:h:")) != -1) {
			switch (c) {
				//Argument to set the program to encode an image
				case 'e':
					if (d_flag == 1) {
						fprintf(stderr, "Can not use -e and -d in the same execution. Please, try again.\n");
						exit(1);
					}
					e_flag = 1;
					break;
				//Argument to set the program to decode an image
				case 'd':
					if (e_flag == 1) {
						fprintf(stderr, "Can not use -e and -d in the same execution. Please, try again.\n");
						exit(1);
					}
					d_flag = 1;
					break;
				//Argument to set the input file
				case 'i':
					i_value = optarg;
					if (strcmp(i_value, "") == 0) {
						fprintf(stderr, "Please, state a image input.\n");
						exit(1);
					}
					break;
				////Argument to set the host image format
				case 'f':
					f_value = optarg;
					if (strcmp(f_value, "") == 0) {
						fprintf(stderr, "Please, state a image format.\n");
						exit(1);
					}
					break;
				case '?':
					if (optopt == 'c') {
						fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					} else if (isprint(optopt)) {
						fprintf(stderr, "Unknown option '%c'.\n", optopt);
					} else {
						fprintf(stderr, "Unkown option character ''\\x%x'\n", optopt);
					}
					return 1;
				default:
					abort();
			}
		} else {
			for (index = optind; index < argc; index++){
				//Test the non-option argument
				//printf ("Non-option argument: %s\n", argv[index]);
				h_value = argv[index];
				if (strcmp(h_value, "") == 0) {
					fprintf(stderr, "Please, state a image output.\n");
					exit(1);
				}
			}
			optind++;
		}
	}

	//Test the arguments
	/*printf ("e_flag = %d, d_flag = %d, i_value = %s, f_value = %s\n",
				e_flag, d_flag, i_value, f_value);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);*/

	run();

	return 0;
}
