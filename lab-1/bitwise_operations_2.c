/**
 * Лабораторная 1. Задание 2.
 *
 * bitwise_operations_2.c -- программа, изменяющая третий байт в числе
 *
 * Copyright (c) 2020, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdio.h>

int main() 
{
    uint32_t var = 0xAABBCCDD;      // Число, которое обрабатывается
    uint32_t input = 0;             // Переменная, куда будет помещено введённое число

    printf("Введите однобайтное число в 16-й с/с.\n");
    scanf("%X", &input);

    var = (var & 0xFF00FFFF) | (input << 16);
    printf("Результат: %X\n", var);

}