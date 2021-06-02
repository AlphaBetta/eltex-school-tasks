/**
 * Лабораторная 7. Задание 1.
 *
 * div.c -- Выполняет деление двух целых чисел. 
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "../mycalc.h"

void div()
{
    int32_t a;
    int32_t b;

    printf("%s", "Enter two integer numbers. (Each number on a new line)\n");
    scanf("%i", &a);
    scanf("%i", &b);
    if (b == 0) {
        fprintf(stderr, "%s", "Division by zero!\n");
        return;
    }
    printf("Result: %i / %i = %i", a, b, a / b);
    return;
}