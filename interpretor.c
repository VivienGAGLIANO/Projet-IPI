#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack.h>
#include <matrix.h>
#include "cursor.h"



int main (int argc, char** argv) {
    //Argument  control
    if (argc<2) {
        printf("%s is to be used with at least 1 argument, but will consider the first one only");
        exit(1);
    }

    size_t lenstr = strlen(argv[1]);
    size_t lensuffix = strlen(".p2g");
    if (!argv[1] || lensuffix > lenstr || !strncmp(argv[1] + lenstr - lensuffix, ".p2g", lensuffix)) {
        printf("Invalid argument name");
        exit(1);
    

    //Variable initialization

    FILE* file = fopen(argv[1], "r");
    


    cursor curs;
    c.pos_x = 0;
    c.pos_y = 0;
    c.dir = right;

    stack s = create_stack();
    
    int width, length;

    char curr.val = 

    

    //
    while ()




    return 0;
}