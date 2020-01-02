#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "matrix.h"
#include "cursor.h"
#include "debugging.h"

/* @requires : nothing
 * @assigns : allocates memory for 500 step structure
 * @ensures : returns a one_step* array of size 500
*/ 
step_list create_step_list() {
    step_list steps = (step_list) malloc(sizeof(one_step)*1000);
    if (steps == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    return steps;
}



/* @requires : valid stack pointer, no cycle in stack
 * @assigns : assigns memory for a new grid
 * @ensures : prints the actual state of the program; i.e. the grid with graduation, as well as cursor position
*/
void print_state(matrix mat, cursor curs, stack s) {
    int w = mat.width;
    int h = mat.height;
    char str[w<h ? h/5 : w/5];
    
    //File is supposed having at least 1 line, so that we don't try to compute log(0)
    int margin_size = log10(h) + 2;
    
    matrix current_grid = create_matrix(h+5, w+margin_size);
    
    //Filling new matrix with ' ' character
    fill_matrix(&current_grid, 32);
    

    //Filling header
    current_grid.grid[0][margin_size] = '0';
    current_grid.grid[1][margin_size] = '|';
    for (int j=1; j<w; j++) {
        if (!(j%5)) {
            //Converting row index in string
            sprintf(str, "%d", j);
            for (int n=0; n<(int) log10(j)+1; n++) {
                current_grid.grid[0][j+2+n] = str[n];
            }
            current_grid.grid[1][j+2] = '|';
        } 
        
    }

    
    //Filling margin
    current_grid.grid[2][margin_size - 1] = '0';
    current_grid.grid[2][margin_size - 1] = '0';
    for (int i=0; i<h; i++) {
        if (!(i%5)) {
            //Converting line index to string
            sprintf(str, "%d", i);
            for (int n=0; n<log10(i)+margin_size; n++)
                current_grid.grid[i+2][n] = str[n];
            current_grid.grid[i+2][margin_size - 1] = '-';
        } 
    }
    current_grid.grid[7][4] = '-';


    //Filling grid
    for (int i=0; i<h; i++) 
        for (int j=0; j<w; j++) 
            current_grid.grid[i+2][j+margin_size] = mat.grid[i][j];
    
    //Cursor position
    current_grid.grid[curs.pos_y + 2][margin_size - 1] = '>';
    current_grid.grid[1][curs.pos_x + margin_size] = 'v';

    //Printing needed stuff
    print_matrix(current_grid);
    printf("\n");
    print_special_stack(s);
    printf("\n");
    printf("x: %i, y: %i", curs.pos_y, curs.pos_x);
    printf("\n");

}


/* @requires : valid char pointer
 * @assigns : nothing
 * @ensures : converts the given command into an integer to switch in main program.
*/
int command_filter(char command[]) {
    if (! strncmp(command, "step", 4))
        return 0;
    if (! strncmp(command, "run", 3))
        return 1;
    if (! strncmp(command, "restart", 7))
        return 2;
    if (! strncmp(command, "quit", 4))
        return 3;
    if (! strncmp(command, "prec", 4))
        return 4;
    if (! strncmp(command, "breakpoint", 10))
        return 5;
    if (! strncmp(command, "removebp", 8))
        return 6;
    if (! strncmp(command, "", 0))
        return 7;
    return -1;
}


/* @requires : valid position pointer, given size must match actual size of position list
 * @assigns : nothing
 * @ensures : tests if given position is in position list
*/
int is_position_in(position pos, position* breakpoints, int size_breakpoints) {
    for (int i=0; i<size_breakpoints; i++)
        if (pos.x == breakpoints[i].x && pos.y == breakpoints[i].y)
            return 1;
    return 0;
}


/* @requires : valid position pointer, given size must match actual size of position list
 * @assigns : modifies position list
 * @ensures : removes all instances of given position from position list, setting them to (-1, -1)
*/
void remove_position(position pos, position* breakpoints, int size_breakpoints) {
    for (int i=0; i<size_breakpoints; i++)
        if (pos.x == breakpoints[i].x && pos.y == breakpoints[i].y) {
            breakpoints[i].x = -1;
            breakpoints[i].y = -1;
        }
} 


