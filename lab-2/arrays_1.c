/**
 * Лабораторная 2. Задание 1.
 *
 * arrays_1.c -- вывод квадратной матрицы по заданному N
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

#define N 5

int main() 
{
    for (int i = 1; i <= N * N; i++) {
        printf("%2u ", i);
        if (i % N == 0) {
            printf("\n");
        }
    } 
}
