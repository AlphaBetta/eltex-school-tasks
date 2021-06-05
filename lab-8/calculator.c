/**
 * Лабораторная 8. Задание 1.
 *
 * calculator.c -- главный файл программы-калькулятора. (Содержит только меню)
 * (Теперь функции арифметических операций выполнены в виде динамической библиотеки)
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "mycalc.h"

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define EXIT 5

/* Функция, выводящая пункты меню */
void print_menu();

int main()
{
    uint8_t option = 0;    // Опция, выбранная пользователем

    while (1) {
        print_menu();
        printf("Enter the selected option:\n");
        scanf("%hhu", &option);    // Считываем опцию, выбранную пользователем
        switch(option) {
            case ADD:
                add();
                break;
            case SUB:
                sub();
                break;
            case MUL:
                mul();
                break;
            case DIV:
                div();
                break;
            case EXIT:
                return 0;
                break;
            default:
                fprintf(stderr, "%s", "Unknown option!\n");
        }       
    }
    return 0;
}

/* Функция, выводящая пункты меню */
void print_menu()
{   
    printf("============================\n");
    printf("Simple calculator.\n");
    printf("Menu:\n");
    printf("1 -- Add two numbers.\n");
    printf("2 -- Subtract two numbers.\n");
    printf("3 -- Multiply two numbers.\n");
    printf("4 -- Divide two numbers.\n");
    printf("5 -- Exit.\n\n");
    return;
}