#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


/** @requires : positive, non zero integers for the matrix' dimension
 *  @assigns : allocates memory for the matrix_elem** 2d table of given size
 *  @ensures : returns a p x q, 0 filled matrix
*/
matrix create_matrix(int p, int q) {
    matrix m;
    m.width = p;
    m.length = q;
    m.grid = (matrix_elem**) malloc(p*sizeof(matrix_elem*));
    for (int i=0; i<p; i++) {
        m.grid[i] = calloc(q, sizeof(matrix_elem));
    }
    return m;
}



/** @requires : valid matrix pointer
 *  @assigns : modifies the matrix' elements
 *  @ensures : sets every element of the matrix equal to the given element
*/
void fill_matrix(matrix* m, matrix_elem elem) {
    matrix new_matrix = create_matrix(m->width, m->length);
    for (int i=0; i<new_matrix.width; i++) {
        for (int j=0; j<new_matrix.length; j++) {
            new_matrix.grid[i][j] = elem;
        }
    }
    *m = new_matrix;
}


/** @requires : nothing
 *  @assigns : nothing
 *  @ensures : prints the matrix' elements as a table
*/
void print_matrix(matrix m) {
    for (int i=0; i<m.width; i++) {
        printf("|");
        for (int j=0; j<m.length; j++) 
            printf("%3i", m.grid[i][j]);
        printf("|\n");
    }
}



int main(int argc, char** argv) {
    int p, q;
    matrix m;
    printf("Dimensions of the matrix ? \n");
    scanf("%i %i", &p, &q);
    m = create_matrix(p,q);
    fill_matrix(&m, 3);
    /*matrix m;
    m.length = 4;
    m.width = 4;
    m.grid = (matrix_elem**) malloc(4*sizeof(matrix_elem*)); 
    for (int i=0; i<4; i++) {
        m.grid[i] = (matrix_elem*) calloc(4, sizeof(matrix_elem));
        for (int j=0; j<4; j++) {
            m.grid[i][j] = i+j;
        }   
    }
    */
    print_matrix(m);
    return 0;
}