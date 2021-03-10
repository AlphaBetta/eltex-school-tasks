/**
 * Лабораторная 4. Задание 1.
 *
 * structs_1.c -- наложение структуры на массив.
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct test {
    char a;
    int32_t b;
};
//} __attribute__((packed));

int main()
{
    char str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};
    struct test* ptr = (struct test*) str;
    
    printf("Первое поле структуры: %c\n", ptr->a);
    printf("Второе поле структуры: %d\n", ptr->b);

    ptr = ptr + 1;

    printf("Первое поле структуры: %c\n", ptr->a);
    printf("Второе поле структуры: %d\n", ptr->b);

    exit(EXIT_SUCCESS);
}