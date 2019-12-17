#ifndef _MATRIX_H
#define _MATRIX_H

//Definition for general element; choose your matrix elements' type by subbing the right type name

typedef int matrix_elem;


//Matrix type construction

struct matrix {
    int length, width;
    matrix_elem** grid;
};
typedef struct matrix matrix;


//Base function for matrix type

matrix create_matrix(int, int);


//Additional functions for matrix type

void fill_matrix(matrix*, matrix_elem);
void print_matrix(matrix);


#endif
