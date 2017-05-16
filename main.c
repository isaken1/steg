#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int e_flag = 0;
	char *i_value = NULL;
	int f_flag = 0;
	char *f_value = NULL;
	int hflag = 0;
	char *h_value = NULL;
	int index;
	int c;

	int opterr = 0;

	while ((c = getopt (argc, argv, "ei:f:h:"))) {
		switch (c) {
			case 'e':
				eflag = 1;
				break;
			case 'i':
				i_value = optarg;
				break;
			
			case 'i':
		}
	}


	return 0;
}
