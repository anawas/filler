#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char module[] = "filler";
const char version[] = "2.1";

void print_help() {
    fprintf(stderr, "Usage: filler [options] -n num of bytes outputfile\n");
    fprintf(stderr, "\nwhere options is some of the following\n");
	fprintf(stderr, "\t-a0          writes out printable chars only [space..0..z]\n");
    fprintf(stderr, "\t-a1          restricts the charachter set to the alphabet [a..z]\n");
    fprintf(stderr, "\t--no-random  characters and numbers are in sequence\n");
    fprintf(stderr, "and\t-n           writes <num of bytes> to <outputfile>\n");
}

int main (int nargs, char **argv) {
	int nbytes, ch, i, start_ch;
	FILE *outf;
    char *outfilename;
    char start, modulo;
	int ascii_flag;
	int abc_flag;
	int random_flag;
	
    printf("\nThis is %s version %s\n\n", module, version);
    
	if (nargs <= 2) {
		fprintf(stderr, "%s ERROR -- missing arguments.\n", module);
        print_help();
		return -1;
	}

    ascii_flag = 0;
	abc_flag = 0;
	random_flag = 1;
	
    for (i = 1; i < nargs; i++) {
		if (strncmp(argv[i], "--no-random", 11) == 0) {
			random_flag = 0;
		} else if (strncmp(argv[i], "-a1", 3) == 0) {
			abc_flag = 1;
			ascii_flag = 1;
		} else if (strncmp(argv[i], "-a0", 3) == 0) {
            ascii_flag = 1;
			abc_flag = 0;
        } else if (strncmp(argv[i], "-n", 2) == 0) {
            ++i; nbytes = atoi(argv[i]);
        } else {
            outfilename = malloc(sizeof(char)*strlen(argv[i]) + 1);
            strcpy(outfilename, argv[i]);
        }
    }

    srand(time(NULL));

    if (ascii_flag == 0) {
        start = 0;
        modulo = 200;
    } else if (abc_flag == 1){
        start = 'a';
        modulo = 'z' - start;
	} else {
        start = ' ';
        modulo = 'z' - start;
    }
	
	if (NULL == (outf = fopen(outfilename, "w"))) {
		fprintf(stderr, "%s ERROR -- Could not open output file %s.\n\n", module, outfilename);
        free(outfilename);
		return -1;
	}

	start_ch = start;
	while (nbytes > 0) {
		if (random_flag == 1) {
			ch = start + rand() % modulo;
		} else {
			ch = start_ch++;
			if (start_ch > start + modulo) {
				start_ch = start;
			}  
		}
		fputc(ch, outf);
		--nbytes;
	}
	fclose(outf);
    free(outfilename);
    
    printf("Wrote file %s.\nquit\n", outfilename);
	return 0;
	
}