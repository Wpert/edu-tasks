#include "matrix_io.h"
#include <stdio.h>
#include <math.h>

static inline double max_d(double a, double b) {
    return (a > b) ? a : b;
}

int init_matrix(double *mat, int n, int s, const char *filename) {
    if (s == 5) {
        if (!filename) {
            fprintf(stderr, "Ошибка: не задано имя файла для формулы 5\n");
            return -1;
        }
        FILE *f = fopen(filename, "r");
        if (!f) {
            fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", filename);
            return -1;
        }
        for (int i = 0; i < n * n; i++) {
            if (fscanf(f, "%lf", &mat[i]) != 1) {
                fprintf(stderr, "Ошибка: недостаточно данных в файле %s\n", filename);
                fclose(f);
                return -1;
            }
        }
        fclose(f);
        return 0;
    }

    double dn = (double)n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double di = (double)i;
            double dj = (double)j;
            int idx = i * n + j;

            switch (s) {
                case 1:
                    mat[idx] = dn - max_d(di, dj);
                    break;
                case 2:
                    mat[idx] = max_d(di, dj);
                    break;
                case 3:
                    mat[idx] = fabs(di - dj);
                    break;
                case 4:
                    mat[idx] = 1.0 / (di + dj + 1.0);
                    break;
                default:
                    fprintf(stderr, "Ошибка: неверный номер формулы %d\n", s);
                    return -1;
            }
        }
    }
    return 0;
}

void print_matrix_segment(const double *mat, int n, int p) {
    int print_n = (p > n) ? n : p;
    for (int i = 0; i < print_n; i++) {
        for (int j = 0; j < print_n; j++) {
            printf("%10.3e ", mat[i * n + j]);
        }
        printf("\n");
    }
}
