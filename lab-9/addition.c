/**
 * Лабораторная 9. Задание 1.
 *
 * add.c -- Выполняет сложение двух целых чисел. 
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdint.h>
#include "func_info.h"

struct func_info func_info_addition = { .func_name = "addition", 
                                        .func_description = "Add two numbers."};



/* Функция складывает два целых числа и возвращает результат */
void addition(void)
{
    int32_t a;
    int32_t b;

    printf("%s", "Enter two integer numbers. (Each number on a new line)\n");
    scanf("%i", &a);
    scanf("%i", &b);
    printf("Result: %i + %i = %i\n", a, b, a + b);
    return;
}