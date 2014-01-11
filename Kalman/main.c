#include <stdio.h>
#include <assert.h>

#include "matrix.h"
#include "cholesky.h"

/**
* \brief Tests matrix inversion using Cholesky decomposition
*/
void matrix_inverse()
{
    int result;

    // data buffer for the original and decomposed matrix
    matrix_data_t d[3 * 3] = { 1, 0.5, 0,
        0.5, 1, 0,
        0, 0, 1 };

    // data buffer for the inverted matrix
    matrix_data_t di[3 * 3] = { 0, 0, 0,
        0, 0, 0,
        0, 0, 0 };

    // prepare matrix structures
    matrix_t m, mi;

    // initialize the matrices
    matrix_init(&m, 3, 3, d);
    matrix_init(&mi, 3, 3, di);

    // decompose matrix to lower triangular
    result = cholesky_decompose_lower(&m);

    // invert matrix using lower triangular
    matrix_invert_lower(&m, &mi);

    // test the result
    matrix_data_t test = matrix_get(&mi, 1, 1);
    assert(test >= 1.3);
}

/*!
* \brief Tests column and row fetching
*/
void matrix_copy_cols_and_rows()
{

    // data buffer for the original and decomposed matrix
    matrix_data_t d[3 * 4] = { 1, 2, 3, 10,
        4, 5, 6, 11,
        7, 8, 9, 12 };

    // data buffer for the copied row
    matrix_data_t v[4] = { 0, 0, 0 };
    matrix_data_t *vp;

    // prepare matrix structure
    matrix_t m;

    // initialize the matrix
    matrix_init(&m, 3, 4, d);

    // fetch the column
    matrix_get_column_copy(&m, 2, v);
    assert(v[0] == 3);
    assert(v[1] == 6);
    assert(v[2] == 9);

    // fetch the row
    matrix_get_row_copy(&m, 2, v);
    assert(v[0] == 7);
    assert(v[1] == 8);
    assert(v[2] == 9);
    assert(v[3] == 12);

    // fetch the row
    matrix_get_row_pointer(&m, 2, &vp);
    assert(vp[0] == 7);
    assert(vp[1] == 8);
    assert(vp[2] == 9);
    assert(vp[3] == 12);
}

/**
* \brief Main entry point
*/
void main()
{
    matrix_inverse();
    matrix_copy_cols_and_rows();
}
