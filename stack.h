#ifndef _STACK_H
#define _STACK_H

//Definition for general element; choose your stack elements' type by subbing the right type name
//The following functions will also need to be adjusted if changing the stack type : pop (for empty stack pop), print_stack

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
void push(stack*, stack_elem);
stack_elem pop(stack*);

//Additional useful functions

void add(stack*, stack_elem, int);
int length_stack(stack);
int find_first_index(stack, stack_elem);
void print_stack(stack);







#endif