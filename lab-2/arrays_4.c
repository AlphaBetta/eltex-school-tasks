/**
 * Лабораторная 2. Задание 4.
 *
 * arrays_4.c -- заполение матрицы числами от 1 до N^2 улиткой.
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

#define N 9

int main()
{
    int32_t matrix[N][N];

    int32_t row = 0;
    int32_t column = 0;

    /* Если == 1, то увеличиваем номер строки/столбца, иначе уменьшаем. */
    uint8_t increase = 1;
    /* Если == 1, то увеличиваем номер столбца, иначе строки. */
    uint8_t turn = 0;

    int16_t cur_num_of_steps = 0;
    int16_t num_of_steps = N;

    uint16_t i = 1;

    /* Заполнение матрицы. */
    while (i <= N * N) {
        if (cur_num_of_steps < num_of_steps) {
            /* Движемся по матрице и заполняем её, пока не нужно будет сделать "поворот". */
            matrix[row][column] = i;
            if (increase) {
                if (turn == 0) {
                    column++;
                } else {
                    row++;
                }
            } else {
                if (turn == 0) {
                    column--;
                } else {
                    row--;
                }
            }
            i++;
            cur_num_of_steps++;
        } else {
            /* Осуществляем "поворот". */

            /* Двигались в таком направлении по матрице: →→→ */
            if ((turn == 0) && increase) {
                turn = 1;
                num_of_steps--;
                cur_num_of_steps = 0;
                column--;
                row++;
                continue;
            }
            /* Двигались в таком направлении по матрице: ↓↓↓ */
            if (turn && increase) {
                turn = 0;
                increase = 0;
                cur_num_of_steps = 0;
                row--;
                column--;
                continue;
            }
            /* Двигались в таком направлении по матрице: ←←← */
            if ((turn == 0) && (increase == 0)) {
                turn = 1;
                num_of_steps--;
                cur_num_of_steps = 0;
                column++;
                row--;
                continue;
            }
            /* Двигались в таком направлении по матрице: ↑↑↑ */
            if (turn && (increase == 0)) {
                turn = 0;
                increase = 1;
                cur_num_of_steps = 0;
                row++;
                column++;
                continue;
            }
        }
    }

    /* Вывод матрицы. */
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            printf("%4i", matrix[i][j - 1]);
            /* Определяем, нужен ли переход на новую строку. */
            if (j % N == 0) {
                printf("\n");
            }
        }
    }
    
    return 0;
}