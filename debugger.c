#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "stack.h"
#include "matrix.h"
#include "cursor.h"
#include "debugging.h"


/* @requires : arguments shouldn't be more than 500 characters long
 * @assigns : memory allocation is done through the interpretor program
 * @ensures : runs the interpretor in debug mode. will not run if invalid argument (i.e. no or non-valid type argument)
*/
int main(int argc, char** argv) {
    //Argument  control

    if (argc<2) {
        printf("%s is to be used with at least 1 argument, but will consider the first one only", argv[0]);
        exit(1);
    }

    size_t lenstr = strlen(argv[1]);
    size_t lensuffix = strlen(".p2g");
    if (!argv[1] || lensuffix > lenstr || !strncmp(argv[1] + lenstr - lensuffix, ".p2g", lensuffix)) {
        printf("Invalid argument format");
        exit(1);
    }

    //Running interpretor in debug mode
    char command[528] = {"DEBUG_MODE=1 ./interpretor "};
    strcat(command, argv[1]);
    system(command);    

    return 0;
}