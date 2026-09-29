#ifndef MATRIX_IO_H
#define MATRIX_IO_H

int init_matrix(double *mat, int n, int s, const char *filename);
void print_matrix_segment(const double *mat, int n, int p);

#endif // MATRIX_IO_H
