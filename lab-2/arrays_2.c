/**
 * Лабораторная 2. Задание 2.
 *
 * arrays_2.c -- вывод массива размером N в обратном порядке
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

#define N 30

int main()
{
    int32_t array[N];

    // Ввод массива.
    for (int i = 1; i <= N; i++) {
        array[i - 1] = i;
    }

    // Вывод массива.
    for (int i = (N - 1); i >= 0; i--) {
        printf("%i ", array[i]);
    }
    printf("\n");

    return 0;
}