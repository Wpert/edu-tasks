#include "matrix_math.h"

void multiply_standard(const double *A, const double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int l = 0; l < n; l++) {
                sum += A[i * n + l] * B[l * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

void transpose_matrix(const double *src, double *dst, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[j * n + i] = src[i * n + j];
        }
    }
}

void multiply_transposed(const double *A, const double *B_t, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int l = 0; l < n; l++) {
                sum += A[i * n + l] * B_t[j * n + l];
            }
            C[i * n + j] = sum;
        }
    }
}
