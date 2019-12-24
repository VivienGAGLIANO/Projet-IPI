#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "stack.h"
#include "matrix.h"
#include "cursor.h"


void actualize(char* new_char, cursor curs, matrix mat) {
    *new_char = mat.grid[curs.pos_y][curs.pos_x];
}


int main (int argc, char** argv) {
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


    //Getting the grid's size

    FILE* file = fopen(argv[1], "r");
    char* first_line = NULL;
    size_t size_buf = 0;
    int nb_char = getline(&first_line, &size_buf, file);
    if (nb_char == -1) {
        perror("Error reading line");
        exit(errno);
    }
    int width, height;
    sscanf(first_line, "%d %d", &width,&height);
    free(first_line);


    //Initializing matrix and retrieving file

    matrix mat = create_matrix(height, width);
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            mat.grid[i][j] = (char) getc(file);
        }
        fseek(file, 1, SEEK_CUR);
    }
    fclose(file);
    //print_matrix(mat);

    //Initializing cursor & stack

    cursor curs;
    curs.pos_x = 0;
    curs.pos_y = 0;
    curs.dir = right;

    stack s = create_stack();
    char curr_val = mat.grid[curs.pos_x][curs.pos_y];
    int a, b, c;
    char ch;


    //Reading and executing instructions until @ character
    //A valid .p2d programm should have a @ character, and the program's execution should lead the cursor to that character, thus ensuring this loop's end for a valid argument
    while (curr_val != '@') {
        switch (curr_val) {
            case '+' :
                push(&s, pop(&s)+pop(&s));
                break;

            case '-' :
                a = pop(&s);
                b = pop(&s);
                push(&s, b-a);
                break;

            case '*' :
                push(&s, pop(&s)*pop(&s));
                break;

            case ':' :
                a = pop(&s);
                b = pop(&s);
                if (a == 0) push(&s, 42);
                push(&s, b/a);
                break;

            case '%' :
                a = pop(&s);
                b = pop(&s);
                if (a == 0) push(&s, 0xbadc0de);
                else push(&s, b%a);
                break;

            case '!' :
                if (!pop(&s)) push(&s, 1);
                else push(&s, 0);
                break;

            case '`' :
                a = pop(&s);
                b = pop(&s);
                push(&s, a<b);
                break;

            case '>' :
                curs.dir = right;
                break;

            case '<' :
                curs.dir = left;
                break;

            case '^' :
                curs.dir = up;
                break;

            case 'v' :
                curs.dir = down;
                break;

            case '?' :
                srandom(time(NULL));
                curs.dir = random() % 8;
                break;

            case '\'' :
                curs.dir = pop(&s)%8;
                break;

            case ']' :
                curs.dir = (curs.dir - 1) % 8;
                break;

            case '[' :
                curs.dir = (curs.dir + 1) % 8;
                break;

            case '_' :
                curs.dir = pop(&s) ? left : right;
                break;

            case '|' :
                curs.dir = pop(&s) ? up : down;
                break;

            case '/' :
                curs.dir = pop(&s) ? down_left : up_right;
                break;

            case '\\' :
                curs.dir = pop(&s) ? up_left : down_right;
                break;

            case '"' :
                //A valid .p2d programm should have " by pairs, thus this loop ends for valid given argument
                move(&curs, curs.dir, mat);
                actualize(&curr_val, curs, mat);
                while (curr_val != '"') {
                    push(&s, (int) curr_val);
                    move(&curs, curs.dir, mat);
                    actualize(&curr_val, curs, mat);
                }
                break;

            case '=' :
                a = pop(&s);
                push (&s, a);
                push (&s, a);
                break;

            case '$' :
                a = pop(&s);
                b = pop(&s);
                push(&s, a);
                push(&s, b);
                break;

            case ';' :
                pop(&s);
                break;

            case '.' :
                printf("%i\n", pop(&s));
                break;

            case ',' :
                a = pop(&s);
                a = a > 255 ? 255 : a;
                a = a < 0 ? 0 : a;
                printf("%c", (char) a);
                break;

            case '#' :
                a = pop(&s);
                for (int i=0; i<a; i++) {
                    move(&curs, curs.dir, mat);
                    actualize(&curr_val, curs, mat);
                }
                break;

            case 'g' :
                a = pop(&s);
                b = pop(&s);
                push(&s, (0<=a && a<=mat.height && 0<=b && b<=mat.width) ? (int) mat.grid[a][b] : 0);
                break;

            case 'p' :
                a = pop(&s);
                b = pop(&s);
                c = pop(&s);
                c = c > 255 ? 255 : c ;
                c = c < 0 ? 0 : c;
                if (0<=a && a<=mat.height && 0<=b && b<=mat.width)
                    mat.grid[a][b] = (char) c;
                break;

            case '&' :
                printf("Enter int : \n");
                scanf("%i", &a);
                push(&s, a);
                break;

            case '~' :
                printf("Type in a char to push (ASCII code) : \n");
                scanf("%c", &ch);
                push(&s, (int) ch);
                break;

            case '0' :
                push(&s, 0);
                break;

            case '1' :
                push(&s, 1);
                break;

            case '2' :
                push(&s,2);
                break;

            case '3' :
                push(&s,3);
                break;

            case '4' :
                push(&s,4);
                break;

            case '5' :
                push(&s,5);
                break;

            case '6' :
                push(&s,6);
                break;

            case '7' :
                push(&s,7);
                break;

            case '8' :
                push(&s,8);
                break;

            case '9' :
                push(&s,9);
                break;

            case ' ' :
                break;

            case '@' :
                return 0;
        }
        //getchar();
        move(&curs, curs.dir, mat);
        actualize(&curr_val, curs, mat);
        /*printf("Cursor : (%i, %i, %i)  Current element : %c  ", curs.pos_x, curs.pos_y, curs.dir, curr_val);
        print_stack(s);
        */
    }

    return 0;
}
