#ifndef _STACK_H
#define _STACK_H


typedef struct cell cell;
typedef cell* stack;

struct cell {
    int head;
    stack tail;
};


//Base functions for stack type

stack create_stack();
void push(stack*, int);
int pop(stack*);

//Additional useful functions

void add(stack*, int, int);
void print_stack(stack);






#endif