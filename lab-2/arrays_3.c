/**
 * Лабораторная 2. Задание 3.
 *
 * arrays_3.c -- заполение верхнего треугольника матрицы 1, а нижнего 0.
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

#define N 8

int main()
{
    int32_t matrix[N][N];
    int32_t zeros = N;

    // Формирование матрицы.
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (j <= (zeros - i)) {
                matrix[i - 1][j - 1] = 0;
            } else {
                matrix[i - 1][j - 1] = 1;
            } 
        }
    }

    // Вывод матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            printf("%2i", matrix[i][j - 1]);
            // Определяем, нужен ли переход на новую строку
            if (j % N == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}