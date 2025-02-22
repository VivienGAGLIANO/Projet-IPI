#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


/** @requires : positive, non zero integers for the matrix' dimension
 *  @assigns : allocates memory for the matrix_elem** 2d table of given size
 *  @ensures : returns a p x q, 0 filled matrix
*/
matrix create_matrix(int p, int q) {
    matrix m;
    m.width = q;
    m.height = p;
    m.grid = (matrix_elem**) malloc(p*sizeof(matrix_elem*));
    if (m.grid == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    for (int i=0; i<p; i++) {
        m.grid[i] = calloc(q, sizeof(matrix_elem));
        if (m.grid[i] == NULL) {
            perror("Memory allocation error");
            exit(1);
        }
    }
    return m;
}



/** @requires : valid matrix pointer
 *  @assigns : modifies the matrix' elements
 *  @ensures : sets every element of the matrix equal to the given element
*/
void fill_matrix(matrix* m, matrix_elem elem) {
    matrix new_matrix = create_matrix(m->height, m->width);
    for (int i=0; i<new_matrix.height; i++) {
        for (int j=0; j<new_matrix.width; j++) {
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
    for (int i=0; i<m.height; i++) {
        for (int j=0; j<m.width; j++)
            printf("%c", m.grid[i][j]);
        printf("\n");
    }
}
