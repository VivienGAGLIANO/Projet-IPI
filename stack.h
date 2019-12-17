#ifndef _STACK_H
#define _STACK_H

//Definition for general element; choose your stack elements' type by subbing the right type name

typedef int stack_elem;


//Stack type construction

typedef struct cell cell;
typedef cell* stack;
struct cell {
    stack_elem head;
    stack tail;
};


//Base functions for stack type

stack create_stack();
void push(stack*, int);
stack_elem pop(stack*);

//Additional useful functions

void add(stack*, int, int);
int length_stack(stack);
int find_first_index(stack, int);
void print_stack(stack);







#endif