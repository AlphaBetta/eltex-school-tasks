/**
 * Лабораторная 3. Задание 1.
 *
 * pointers_1.c -- программа, выводящяя побайтово число с использованием указателей
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
    uint8_t* pointer = &var;

    for (int i = 1; i <= sizeof(var); i++) {

        printf("%d byte: %X\n", i, *pointer);
        pointer = pointer + 1;
    }

    return 0;
}