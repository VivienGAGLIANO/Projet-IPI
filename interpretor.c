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

/* @requires : cursor and matrix must be in each other's range
 * @assigns : modifies new_char value
 * @ensures : sets new_char's value to the element in matrix located in cursor's coordinate 
 */
void update(char* new_char, cursor curs, matrix mat) {
    *new_char = mat.grid[curs.pos_y][curs.pos_x];
}


/* @requires : valid .p2d program, in the sense that characters are disposed such as the cursor will always meet a @ if following the instructions
 * @assigns : modifies all given argument
 * @ensures : runs one step of the program, and updates its state
*/
void run_one_step(matrix* mat, cursor* curs, stack* s, char* curr_val) {
    int a, b, c;
    char ch;
    
    switch (*curr_val) {
            case '+' :
                push(s, pop(s)+pop(s));
                break;

            case '-' :
                a = pop(s);
                b = pop(s);
                push(s, b-a);
                break;

            case '*' :
                push(s, pop(s)*pop(s));
                break;

            case ':' :
                a = pop(s);
                b = pop(s);
                if (a == 0) push(s, 42);
                push(s, b/a);
                break;

            case '%' :
                a = pop(s);
                b = pop(s);
                if (a == 0) push(s, 0xbadc0de);
                else push(s, b%a);
                break;

            case '!' :
                if (!pop(s)) push(s, 1);
                else push(s, 0);
                break;

            case '`' :
                a = pop(s);
                b = pop(s);
                push(s, a<b);
                break;

            case '>' :
                (*curs).dir = right;
                break;

            case '<' :
                (*curs).dir = left;
                break;

            case '^' :
                (*curs).dir = up;
                break;

            case 'v' :
                (*curs).dir = down;
                break;

            case '?' :
                srandom(time(NULL));
                (*curs).dir = random() % 8;
                break;

            case '\'' :
                (*curs).dir = pop(s)%8;
                break;

            case ']' :
                (*curs).dir = ((*curs).dir - 1) % 8;
                break;

            case '[' :
                (*curs).dir = ((*curs).dir + 1) % 8;
                break;

            case '_' :
                (*curs).dir = pop(s) ? left : right;
                break;

            case '|' :
                (*curs).dir = pop(s) ? up : down;
                break;

            case '/' :
                (*curs).dir = pop(s) ? down_left : up_right;
                break;

            case '\\' :
                (*curs).dir = pop(s) ? up_left : down_right;
                break;

            case '"' :
                move(curs, (*curs).dir, *mat);
                update(curr_val, (*curs), *mat);
                
                //A valid .p2d programm should have " by pairs, thus this loop ends for valid given argument
                while (*curr_val != '"') {
                    push(s, (int) *curr_val);
                    move(curs, (*curs).dir, *mat);
                    update(curr_val, (*curs), *mat);
                }
                break;

            case '=' :
                a = pop(s);
                push (s, a);
                push (s, a);
                break;

            case '$' :
                a = pop(s);
                b = pop(s);
                push(s, a);
                push(s, b);
                break;

            case ';' :
                pop(s);
                break;

            case '.' :
                printf("%i\n", pop(s));
                break;

            case ',' :
                a = pop(s);
                a = a > 255 ? 255 : a;
                a = a < 0 ? 0 : a;
                printf("%c", (char) a);
                break;

            case '#' :
                a = pop(s);
                for (int i=0; i<a; i++) {
                    move(curs, (*curs).dir, *mat);
                    update(curr_val, (*curs), *mat);
                }
                break;

            case 'g' :
                a = pop(s);
                b = pop(s);
                push(s, (0<=a && a<=(*mat).height && 0<=b && b<=(*mat).width) ? (int) (*mat).grid[a][b] : 0);
                break;

            case 'p' :
                a = pop(s);
                b = pop(s);
                c = pop(s);
                c = c > 255 ? 255 : c ;
                c = c < 0 ? 0 : c;
                if (0<=a && a<=(*mat).height && 0<=b && b<=(*mat).width)
                    (*mat).grid[a][b] = (char) c;
                break;

            case '&' :
                printf("Enter int : \n");
                scanf("%i", &a);
                push(s, a);
                break;

            case '~' :
                printf("Type in a char to push (ASCII code) : \n");
                scanf("%c", &ch);
                push(s, (int) ch);
                break;

            case '0' :
                push(s, 0);
                break;

            case '1' :
                push(s, 1);
                break;

            case '2' :
                push(s,2);
                break;

            case '3' :
                push(s,3);
                break;

            case '4' :
                push(s,4);
                break;

            case '5' :
                push(s,5);
                break;

            case '6' :
                push(s,6);
                break;

            case '7' :
                push(s,7);
                break;

            case '8' :
                push(s,8);
                break;

            case '9' :
                push(s,9);
                break;

            case ' ' :
                break;

            case '@' :
                perror("@ character shouldn't be met in loop");
                exit(1);
        }
        move(curs, (*curs).dir, *mat);
        update(curr_val, (*curs), *mat);
}



/* @requires : valid .p2d program, in the sense that characters are disposed such as the cursor will always meet a @ if following the instructions
 * @assigns : temporarily allocates memory for buffer when getting first line. allocates as well memory for the grid serving as copy of the file.
 * @ensures : runs the given .p2d program. auto-controls the argument number and type.
 */
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
    

    //Debugger settings------------------------------------------------
    
    //Enables/disables debug mode
    int debug_mode = (argc > 2) && (! strcmp(argv[2], "1"));
    
    //Allows program to run one step
    int should_run = 1;
    
    //Controls last entered command validity 
    int invalid_command = 0;

    //Variable used for run command control
    int run_mode = 0;

    //Variable used for user input control
    char input[256];
    char command[256];
    int p,q;
    
    //Variable used for step n command
    int skip_debug = 0;

    //Variable used for breakpoint control
    position curr_pos;
    position bpoint;
    
    //Creating array to memorize different steps    
    step_list steps = create_step_list();
    int step_list_size = 1000;
    int step_count = 0;
    steps[step_count].grid = mat;
    steps[step_count].stack = s;
    steps[step_count].curs = curs;

    //Creating array to memorize breakpoints, and initializing all positions to (-1, -1)
    position* breakpoints = (position*) malloc(15*sizeof(position));
    if (breakpoints == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    for (int i=0; i<(int) sizeof(breakpoints); i++) {
        breakpoints[i].x = -1;
        breakpoints[i].y = -1;
    }
    int breakpoints_count = 0;
    int breakpoints_size = 15;


    //-----------------------------------------------------------------


    //Reading and executing instructions until @ character
    //A valid .p2d programm should have a @ character, and the program's execution should lead the cursor to that character, thus ensuring this loop's end for a valid argument
    while (curr_val != '@') {
        
        //Checking if current position is a breakpoint
        curr_pos.x = curs.pos_x;
        curr_pos.y = curs.pos_y;
        if (is_position_in(curr_pos, breakpoints, breakpoints_size)) {
            debug_mode = 1;
            run_mode = 0;
            skip_debug = 0;
        }
            

        //Debug mode---------------------------------------------------
        if (debug_mode && !skip_debug) {
            system("clear");
            print_state(mat, curs, s);
            printf("\n\n");

            should_run = 0;
            p = 1;
            q = 1;

            if (invalid_command) {
                printf("Invalid command, please retry\n\n");
                invalid_command = 0;
            }


            //Getting command from user
            fgets(input, 256, stdin);
            sscanf(input, "%s %i %i", command, &p, &q);
            bpoint.x = p;
            bpoint.y = q;
            switch (command_filter(command)) {
                case 0 : //step
                    if (p<=0) {
                        printf("Can only go forward a strictly positive number of steps\nPlease try again\n");
                        sleep(2.5);
                    } 
                    else {
                        skip_debug += p;
                        should_run = 1;
                    }
                    break;

                case 1 : //run
                    run_mode = 1;
                    debug_mode = 0;
                    should_run = 1;
                    break;

                case 2 : //restart
                    step_count = 0;
                    mat = steps[step_count].grid;
                    curs = steps[step_count].curs;
                    s = steps[step_count].stack;
                    break;

                case 3 : //quit
                    system("clear");
                    return 0;
                    break;

                case 4 : //prec
                    if (p<=0) {
                        printf("Can only go backward a strictly positive number of steps\nPlease try again\n");
                        sleep(2.5);
                    }
                    else {
                        if (step_count - p < 0) {
                            printf("Can't go back that far\nPlease try again\n");
                            sleep(2.5);
                        }
                        else {
                            step_count -= p;
                            mat = steps[step_count].grid;
                            curs = steps[step_count].curs;
                            s = steps[step_count].stack;
                        }
                    }
                    break;

                case 5 : //breakpoint
                    if (p<0 || p>= width || q<0 || q>= height) {
                        printf("Coordinates out of range\nPlease try again\n");
                        sleep(2.5);
                    }
                    else {
                        breakpoints_count++;

                        //Reallocating memory if breakpoint list is filled
                        if (breakpoints_count >= breakpoints_size) {
                            breakpoints_size += 15;
                            breakpoints = (position*) realloc(breakpoints, breakpoints_size*sizeof(position));
                            if (breakpoints == NULL) {
                                perror("Memory allocation error");
                                exit(1);
                            }
                        }

                        breakpoints[breakpoints_count - 1] = bpoint;
                    }
                    break;

                case 6 : //removebp
                    
                    if (p<0 || p>= width || q<0 || q>= height) {
                        printf("Coordinates out of range\nPlease try again\n");
                        sleep(2.5);
                    }
                    else {
                        if (is_position_in(bpoint, breakpoints, breakpoints_size)) {
                            breakpoints_count--;
                            remove_position(bpoint, breakpoints, breakpoints_size);
                        }
                    }
                    break;

                case 7 : //empty
                    break;

                default :
                    invalid_command = 1;
                    break;
            }
            system("clear");
        }
        //-------------------------------------------------------------


        if (should_run) {
            run_one_step(&mat, &curs, &s, &curr_val);
        
            //Updating step list
            step_count++;
            if (!run_mode)
                skip_debug--;
            

            //Reallocating space if needed for steps storing
            if (step_count >= step_list_size) {
                step_list_size += 1000;
                steps = realloc(steps, step_list_size*sizeof(one_step));
                if (steps == NULL) {
                    perror("Memory allocation error");
                    exit(1);
                }
            }

            steps[step_count].stack = s;
            steps[step_count].curs = curs;
            steps[step_count].grid = mat;
        }
    }
    return 0;
}
