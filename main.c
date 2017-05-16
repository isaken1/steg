#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int e_flag = 0;
	int d_flag = 0;
	char *i_value = NULL;
	char *f_value = NULL;
	char *h_value = NULL;
	int index;
	int c;

	int opterr = 0;


	while (index < argc) {
		if ((c = getopt (argc, argv, "edi:f:h:")) != -1) {
			switch (c) {
				//Argument to set the program to encode an image
				case 'e':
					d_flag = 0;
					e_flag = 1;
					break;
				//Argument to set the program to decode an image
				case 'd':
					d_flag = 1;
					e_flag = 0;
				//Argument to set the input file
				case 'i':
					i_value = optarg;
					break;
				////Argument to set the host image format
				case 'f':
					f_value = optarg;
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
			for (index = optind; index < argc; index++)
				//Test the non-option argument
				printf ("Non-option argument: %s\n", argv[index]);
				h_value = argv[index];
			optind++;
		}
	}

	//Test the arguments
	/*printf ("e_flag = %d, d_flag = %d, i_value = %s, f_value = %s\n",
				e_flag, d_flag, i_value, f_value);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);*/
	return 0;
}
