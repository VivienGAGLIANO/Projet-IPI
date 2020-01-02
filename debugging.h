#ifndef _DEBUGGING_H
#define _DEBUGGING_H
#include "matrix.h"
#include "stack.h"
#include "cursor.h"


//Structure declaration and base function necessary for debugger
typedef struct {
    int x, y;
} position;


typedef struct {
    matrix grid;
    cursor curs;
    stack stack;
} one_step;


typedef one_step* step_list;
step_list create_step_list();
int is_position_in(position, position*, int);
void remove_position(position, position*, int);


//Auxiliary functions for debugger
void print_state(matrix, cursor, stack);
int command_filter(char*);


#endif