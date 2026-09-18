#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_math.h"
#include "matrix_io.h"

static double get_time_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Использование: %s k n f1 f2 p [<file1> <file2>]\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    int f1 = atoi(argv[3]);
    int f2 = atoi(argv[4]);
    int p = atoi(argv[5]);

    if (k <= 0 || n <= 0 || p <= 0) {
        fprintf(stderr, "Ошибка: k, n, p должны быть положительными числами.\n");
        return 1;
    }

    const char *file1 = NULL;
    const char *file2 = NULL;
    int arg_idx = 6;

    if (f1 == 5) {
        if (arg_idx >= argc) { fprintf(stderr, "Отсутствует имя файла для f1=5\n"); return 1; }
        file1 = argv[arg_idx++];
    }
    if (f2 == 5) {
        if (arg_idx >= argc) { fprintf(stderr, "Отсутствует имя файла для f2=5\n"); return 1; }
        file2 = argv[arg_idx++];
    }

    size_t mem_size = (size_t)n * n * sizeof(double);
    double* A   = (double*)malloc(mem_size);
    double* B   = (double*)malloc(mem_size);
    double* B_t = (double*)malloc(mem_size);
    double* C   = (double*)malloc(mem_size);

    if (!A || !B || !B_t || !C) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        free(A); free(B); free(B_t); free(C);
        return 1;
    }

    if (init_matrix(A, n, f1, file1) != 0 || init_matrix(B, n, f2, file2) != 0) {
        free(A); free(B); free(B_t); free(C);
        return 1;
    }

    printf("=== Запуск тестов: размер %dx%d, итераций %d ===\n", n, n, k);

    double t_start = get_time_sec();
    for (int iter = 0; iter < k; iter++) {
        multiply_standard(A, B, C, n);
    }
    double t_end = get_time_sec();
    double time_standard = t_end - t_start;

    printf("\n--- Результат стандартного умножения ---\n");
    print_matrix_segment(C, n, p);
    printf("Время выполнения: %.6f сек\n", time_standard);

    transpose_matrix(B, B_t, n);

    t_start = get_time_sec();
    for (int iter = 0; iter < k; iter++) {
        multiply_transposed(A, B_t, C, n);
    }
    t_end = get_time_sec();
    double time_transposed = t_end - t_start;

    printf("\n--- Результат умножения с транспонированием ---\n");
    print_matrix_segment(C, n, p);
    printf("Время выполнения: %.6f сек\n", time_transposed);

    if (time_transposed > 0.0) {
        printf("\nУскорение: %.2fx\n", time_standard / time_transposed);
    }

    free(A);
    free(B);
    free(B_t);
    free(C);

    return 0;
}
