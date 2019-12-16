#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/** @requires : nothing
 *  @assigns : nothing
 *  @ensures : create empty stack as a NULL pointer
 */
stack create_stack() {
    return NULL;
}


/** @requires : valid stack pointer
 *  @assigns : modifies the stack
 *  @ensures : adds the element at the stack's head
*/
void push(stack *s, int element) {
    stack new_cell;
    new_cell = (stack) malloc(sizeof(int));
    new_cell->head = element;
    new_cell->tail = *s;
    *s = new_cell;
}


/** @requires : valid stack pointer
 *  @assigns : modifies the stack
 *  @ensures : removes the last element of the stack, and returns its value 
 */
int pop(stack *s) {
    int n = (*s)->head;
    *s = (*s)->tail;
    return n;
}


/** @requires : valid stack pointer, index within stack range (index <= length_stack(s))
 *  @assigns : modifies the stack
 *  @ensures : adds element at the index-th case of the stack
 */
void add(stack* s, int element, int index) {
    stack tmp, new_cell; 
    tmp = *s;
    new_cell = (stack) malloc(sizeof(int));
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


/** @requires : valid stack pointer
 *  @assigns : nothing
 *  @ensures : returns the stack's length
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


/** @requires : valid stack pointer, no cycle in the stack
 *  @assigns : nothing
 *  @ensures : returns the element's first index in the stack, -1 if it's not in it
 */
int find_first_index(stack s, int element) {
    int index = -1;
    int count = 0;
    while (index == -1 || s != NULL) {
        if (s->head == element) index = count;
        s = s->tail;
        count++;
    }
    return index;
}


/** @requires : valid stack pointer, no cycle in the stack
 *  @assigns : nothing
 *  @ensures : prints the stack
*/
void print_stack(stack s) {
    if (s->tail == NULL) {
        printf("[%3i]\n", s->head);
    }
    else {
        printf("[%3i] -> ", s->head);
        print_stack(s->tail);
    }
}

int main(int argc, char** argv) {
    stack s = create_stack();
    for (int i=0; i<10; i++) {
        push(&s, i);
    }
    printf("%i\n", find_first_index(s, 3));
    print_stack(s);
    return 0;
}