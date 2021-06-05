/**
 * Лабораторная 8. Задание 1.
 *
 * sub.c -- Выполняет вычитание двух целых чисел. 
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "mycalc.h"

/* Функция вычитает два целых числа и возвращает результат */
void sub()
{
    int32_t a;
    int32_t b;

    printf("%s", "Enter two integer numbers. (Each number on a new line)\n");
    scanf("%i", &a);
    scanf("%i", &b);
    printf("Result: %i - %i = %i\n", a, b, a - b);
    return;
}