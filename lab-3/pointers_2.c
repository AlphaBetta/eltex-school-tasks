/**
 * Лабораторная 3. Задание 2.
 *
 * pointers_2.c -- программа, изменяющая третий байт в числе с помощью указателей
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

int main()
{
    uint32_t var = 0xAABBCCDD;      // Число, которое обрабатывается
    uint16_t input = 0;              // Переменная, куда будет помещено введённое число
    uint8_t* pointer = (uint8_t*) &var;
    pointer = pointer + 2;

    printf("Введите однобайтное число в 16-й с/с.\n");
    scanf("%hX", &input);

    printf("Неизменённое число: %X\n", var);

    *pointer = input;

    printf("Изменённое число: %X\n", var);

    return 0;
}