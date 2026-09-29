#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "matrix_math.h"
#include "matrix_io.h"

static double get_time_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int compare_matrices(const double *C1, const double *C2, int n) {
    double max_diff = 0.0;
    for (int i = 0; i < n * n; i++) {
        double d = fabs(C1[i] - C2[i]);
        if (d > max_diff) max_diff = d;
    }
    printf("  Макс. разница: %.3e\n", max_diff);
    return max_diff < 1e-9;
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
        fprintf(stderr, "Ошибка: k, n, p должны быть положительными.\n");
        return 1;
    }

    const char *file1 = NULL, *file2 = NULL;
    int arg_idx = 6;
    if (f1 == 5) file1 = argv[arg_idx++];
    if (f2 == 5) file2 = argv[arg_idx++];

    size_t mem_size = (size_t)n * n * sizeof(double);
    double *A     = malloc(mem_size);
    double *B     = malloc(mem_size);
    double *B_t   = malloc(mem_size);
    double *C_std = malloc(mem_size);
    double *C_tr  = malloc(mem_size);

    if (!A || !B || !B_t || !C_std || !C_tr) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    if (init_matrix(A, n, f1, file1) != 0 ||
        init_matrix(B, n, f2, file2) != 0) {
        return 1;
    }

    printf("=== Тест: %dx%d, k=%d итераций ===\n\n", n, n, k);

    double t0 = get_time_sec();
    for (int iter = 0; iter < k; iter++) {
        multiply_standard(A, B, C_std, n);
    }
    double time_standard = get_time_sec() - t0;

    double t1 = get_time_sec();
    transpose_matrix(B, B_t, n);
    double time_transpose = get_time_sec() - t1;

    double t2 = get_time_sec();
    for (int iter = 0; iter < k; iter++) {
        multiply_transposed(A, B_t, C_tr, n);
    }
    double time_transposed = get_time_sec() - t2;

    double time_total = time_transpose + time_transposed;

    // --- Проверка ---
    printf("--- Проверка корректности ---\n");
    compare_matrices(C_std, C_tr, n);

    printf("\n--- Результат (сегмент %dx%d) ---\n", p, p);
    print_matrix_segment(C_std, n, p);

    double avg_std = time_standard / k;
    double avg_tr  = time_transposed / k;
    double avg_tot = time_total / k;

    printf("\n--- Времена ---\n");
    printf("Стандартное умножение (k=%d):\n", k);
    printf("   всего:              %10.6f сек\n", time_standard);
    printf("   в среднем:          %10.6f сек/итер\n", avg_std);

    printf("Транспонирование (1 раз):\n");
    printf("   всего:              %10.6f сек\n", time_transpose);

    printf("Умножение с трансп. (k=%d):\n", k);
    printf("   всего:              %10.6f сек\n", time_transposed);
    printf("   в среднем:          %10.6f сек/итер\n", avg_tr);

    printf("Полное (трансп. + умножение):\n");
    printf("   всего:              %10.6f сек\n", time_total);
    printf("   в среднем:          %10.6f сек/итер\n", avg_tot);

    printf("\n--- Анализ ---\n");
    printf("Ускорение только умножения:       %.2fx\n", time_standard / time_transposed);
    printf("Ускорение с учётом трансп.:       %.2fx\n", time_standard / time_total);
    printf("Доля транспонирования:            %.2f%%\n",
           100.0 * time_transpose / time_total);

    printf("\nЭкономия на итерацию:\n");
    printf("   абсолютная:  %10.6f сек\n", avg_std - avg_tr);
    printf("   относительная: %.1f%%\n", 100.0 * (avg_std - avg_tr) / avg_std);

    free(A); free(B); free(B_t); free(C_std); free(C_tr);
    return 0;
}
