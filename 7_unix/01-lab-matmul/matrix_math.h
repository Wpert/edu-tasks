// надо будет узнать есть ли #pragma once на Си
// не верю что такой простой вещи да не добавить

#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

void multiply_standard(const double *A, const double *B, double *C, int n);
void transpose_matrix(const double *src, double *dst, int n);
void multiply_transposed(const double *A, const double *B_t, double *C, int n);

#endif // MATRIX_MATH_H
