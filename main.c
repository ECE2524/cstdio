#include <libgen.h> //for basename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"

#define MAX_PROG_NAME_LEN 254

int f_flags;
char progname[MAX_PROG_NAME_LEN+1];

void usage(FILE* fpo, int status) {
    fprintf(fpo, "\
usage: %s [options] [FILE...]\n\
",progname);
    exit(status);
}

void setprogname(char* str) {
    strncpy(progname, basename(str), MAX_PROG_NAME_LEN);
}

void errmsg(const char* str) {
    char buffer[1024];
    strcpy(buffer,progname);
    strcat(buffer, ": ");
    strncat(buffer, str, 1024-strlen(buffer));
    perror(buffer);
}

int main(int argc, char *argv[]) {
    int opt = 0;
    f_flags = 0;
    extern int optind;

    setprogname(argv[0]);
    
    while ((opt = getopt(argc, argv, "dqvh")) != -1) {
        switch (opt) {
        case 'd':
            f_flags |= F_DEBUG;
            break;
        case 'v':
            f_flags |= F_VERBOSE;
            break;
        case 'q':
            f_flags |= F_QUIET;
            break;
        case 'h':
            usage(stdout, 0);
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    argc -= optind;
    argv += optind;

    
    if (argc == 0) {
        if (DEBUG)
            fprintf(stderr, "no file arguments, reading from standard in\n");
        // do something with stdin?
    }

    // do something with each file given as argument
    for(; argc > 0; argc -= 1, argv +=1) {
        FILE *fpo;
        if (DEBUG)
            fprintf(stderr, "file argument: %s\n", *argv);
        if ((fpo = fopen(*argv, "r")) == NULL) {
            errmsg(*argv);
            //can we continue on an error, or should be break out of
            //the loop?
        } else {
            // Do something with fpo
            // and don't forget to close it!
            fclose(fpo);
        }
    } 

    exit(EXIT_SUCCESS);
}
