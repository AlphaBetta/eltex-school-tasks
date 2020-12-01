/**
 * Лабораторная 1. Задание 1.
 *
 * bitwise_operations_1.c -- программа, выводящее побайтово число
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
    uint32_t ones = 0x000000FF;     // Число, где один байт состоит из единиц, а все остальные из нулей

    for (int i = 0; i < 4; i++) {
        uint8_t result = (var & ones) >> (8 * i);     // Сначала применяем логическое И, затем сдвиг в зависимости от того, какой байт обрабатывается сейчас
        printf("%d byte: %X\n", i + 1, result);
        ones = ones << 8;   // Сдвигаем байт, состоящий из единиц на 1 байт
    }
}
