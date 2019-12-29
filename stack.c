#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* @requires : nothing
 * @assigns : nothing
 * @ensures : create empty stack as a NULL pointer
*/
stack create_stack() {
    return NULL;
}


/* @requires : valid stack pointer
 * @assigns : modifies the stack
 * @ensures : adds the element at the stack's head
*/
void push(stack *s, stack_elem element) {
    stack new_cell;
    new_cell = (stack) malloc(sizeof(int));
    if (new_cell == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    new_cell->head = element;
    new_cell->tail = *s;
    *s = new_cell;
}


/* @requires : valid stack pointer
 * @assigns : modifies the stack
 * @ensures : removes the last element of the stack, and returns its value. Returns 0 if stack is empty
*/
stack_elem pop(stack *s) {
    if (*s == NULL)
        return 0;
    stack_elem n = (*s)->head;
    *s = (*s)->tail;
    return n;
}


/* @requires : valid stack pointer, index within stack range (index <= length_stack(s))
 * @assigns : modifies the stack
 * @ensures : adds element at the index-th case of the stack
*/
void add(stack* s, stack_elem element, int index) {
    stack tmp, new_cell;
    tmp = *s;
    new_cell = (stack) malloc(sizeof(int));
    if (new_cell == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    new_cell->head = element;
    if (index == 0) {
        new_cell->tail = tmp;
        *s = new_cell;
    }
    else {
        for (int i=1; i<index; i++) {
            tmp = tmp->tail;
        new_cell->tail = tmp->tail;
        }
        tmp->tail = new_cell;
    }

}


/* @requires : valid stack pointer
 * @assigns : nothing
 * @ensures : returns the stack's length
*/
int length_stack(stack s) {
    int count = 0;
    stack tmp = s;
    if (s != NULL) {
        while (tmp != NULL) {
            tmp = tmp->tail;
            count ++;
        }
    }
    return count;
}


/* @requires : valid stack pointer, no cycle in the stack
 * @assigns : nothing
 * @ensures : returns the element's first index in the stack, -1 if it's not in it
*/
int find_first_index(stack s, stack_elem element) {
    int index = -1;
    int count = 0;
    while (index == -1 || s != NULL) {
        if (s->head == element) index = count;
        s = s->tail;
        count++;
    }
    return index;
}


/* @requires : valid stack pointer, no cycle in the stack
 * @assigns : nothing
 * @ensures : prints the stack
*/
void print_stack(stack s) {
    if (s == NULL)
        printf("Empty stack\n");
    else {
        if (s->tail == NULL)
            printf("[%1i]\n", s->head);
        else {
            printf("[%3i] -> ", s->head);
            print_stack(s->tail);
        }
    }
}


/* @requires : nothing
 * @assigns : nothing
 * @ensures : returns i, truncated to the [0; 255] set. 
*/
static int truncate(int i) {
    return i>255 ? 255 : (i<0 ? 0 : i);
}


/* @requires : valid stack pointer, no cycle in the stack
 * @assigns : nothing
 * @ensures : prints the stack, specifying in parenthisis the character corresponding to the ASCII code (truncated to [0;255]) of each element
*/
void print_special_stack(stack s) {
    if (s == NULL)
        printf("Empty stack\n");
    else {
        if (s->tail == NULL)
            printf("%i (%c)| |\n", s->head, (char) truncate(s->head));
        else {
            printf("%i (%c)| ", s->head, (char) truncate(s->head));
            print_special_stack(s->tail);
        }
    }
}
