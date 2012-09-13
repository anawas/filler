#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char module[] = "filler";
const char version[] = "2.0";

void print_help() {
    fprintf(stderr, "Usage: filler [-a] -n num of bytes outputfile\n");
    fprintf(stderr, "\nwhere\t-a\twrites out printable chars only [space..0..z]\n");
    fprintf(stderr, "\t-n\twrites <num of bytes> to <outputfile>\n");
}

int main (int nargs, char **argv) {
	int nbytes, ch, i;
	FILE *outf;
    char *outfilename;
    char start, modulo;
	int ascii_flag;
    
    printf("\nThis is %s version %s\n\n", module, version);
    
	if (nargs <= 2) {
		fprintf(stderr, "%s ERROR -- missing arguments.\n", module);
        print_help();
		return -1;
	}

    ascii_flag = 0;
    for (i = 1; i < nargs; i++) {
        if (strncmp(argv[i], "-a", 2) == 0) {
            ascii_flag = 1;
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
    } else {
        start = ' ';
        modulo = 'z' - start;
    }
	
	if (NULL == (outf = fopen(outfilename, "w"))) {
		fprintf(stderr, "%s ERROR -- Could not open output file %s.\n\n", module, outfilename);
        free(outfilename);
		return -1;
	}

	while (nbytes > 0) {
		ch = start + rand() % modulo;
		fputc(ch, outf);
		--nbytes;
	}
	fclose(outf);
    free(outfilename);
    
    printf("Wrote file %s.\nquit\n", outfilename);
	return 0;
	
}