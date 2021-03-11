/**
 * Лабораторная 4. Задание 2.
 *
 * structs_2.c -- программа, реализующая телефонный справочник с помощью структур.
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

//TODO Спросить, почему в справочнике помещается 11 записей

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_LENGTH 100
#define PHONE_NUMBER_LENGTH 13
#define PHONEBOOK_LENGTH 10

#define ADD 1
#define SHOW 2
#define DELETE 3
#define FIND 4
#define EXIT 5


/* Структура, описывающая абонента */
typedef struct _subscriber {
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    char phone_number[PHONE_NUMBER_LENGTH];
} subscriber;

/* Функция, выводящая пункты меню */
void print_menu();

/* Добавить абонента */
void add_subscriber(subscriber phonebook[], uint16_t index);

/* Вывести всех абонентов */
void print_all_subscribers(subscriber phonebook[], uint16_t num_subscribers);

/* Удалить абонента */
void delete_subscriber(subscriber phonebook[], uint16_t* index, uint16_t* num_subscribers);

/* Найти абонента и вывести его */
void find_subscriber(subscriber phonebook[], uint16_t num_subscribers);

int main()
{
    subscriber phonebook[PHONEBOOK_LENGTH];      // Массив абонентов
    uint16_t option = 0;                         // Опция, выбранная пользователем
    uint16_t index = 0;                          // Хранит номер текущей свободной ячейки
    uint16_t num_subscribers = 0;                // Количество абонентов в справочнике 

    while (option != EXIT) {
        print_menu();
        printf("Введите выбранную опцию:\n");
        scanf("%hu", &option);                  // Считываем опцию, выбранную пользователем
        switch(option) {
            case ADD:
                /* Если справочник не заполнен, то добавляем абонента */
                if (num_subscribers <= PHONEBOOK_LENGTH) {
                    add_subscriber(phonebook, index);
                    num_subscribers++;
                    index++;
                } else {
                    printf("В справочнике нет свободного места!\n");
                    continue;
                }
                break;
            case SHOW:
                print_all_subscribers(phonebook, num_subscribers);
                break;
            case DELETE:
                delete_subscriber(phonebook, &index, &num_subscribers);
                break;
            case FIND:
                find_subscriber(phonebook, num_subscribers);
                break;
        }       
    }

    
    exit(EXIT_SUCCESS);
}

/* Функция, выводящая пункты меню */
void print_menu()
{
    printf("============================\n");
    printf("Телефонный справочник\n");
    printf("Меню:\n");
    printf("1 -- Добавить абонента.\n");
    printf("2 -- Вывести всех абонентов.\n");
    printf("3 -- Удалить абонента.\n");
    printf("4 -- Найти абонента.\n");
    printf("5 -- Выйти из справочника.\n\n");

    return;
}

/* Добавить абонента */
void add_subscriber(subscriber phonebook[], uint16_t index)
{
    printf("Введите данные нового абонента.\n");
    scanf("%s", phonebook[index].name);
    scanf("%s", phonebook[index].surname);
    scanf("%s", phonebook[index].phone_number);

    return;
}

/* Вывести всех абонентов */
void print_all_subscribers(subscriber phonebook[], uint16_t num_subscribers)
{
    for (uint16_t i = 0; i < num_subscribers; i++) {
        if ((phonebook[i].name[0] != '0') && (phonebook[i].surname[0] != '0')) {
            printf("%s %s %s\n", phonebook[i].name, phonebook[i].surname, phonebook[i].phone_number);
        }
    }
    return;
}

/* Удалить абонента */
void delete_subscriber(subscriber phonebook[], uint16_t* index, uint16_t* num_subscribers)
{
    char input[NAME_LENGTH];

    printf("Введите имя абонента, которого вы хотите удалить.\n");
    scanf("%s", input);

    for (uint16_t i; i < *num_subscribers; i++) {
        if (strcmp(phonebook[i].name, input) == 0) {
            /* Зануляем имя и фамилию */
            for (uint16_t j = 0; j < NAME_LENGTH; j++) {
                phonebook[i].name[j] = '0';
                phonebook[i].surname[j] = '0';
            }
            /* Зануляем телефон */
            for (uint16_t k = 0; k < PHONE_NUMBER_LENGTH; k++) {
                phonebook[i].name[k] = '0';
                phonebook[i].surname[k] = '0';
            }
            *index = i;
            *num_subscribers = *num_subscribers - 1;
        }
    }

    return;
}

/* Найти абонента и вывести его */
void find_subscriber(subscriber phonebook[], uint16_t num_subscribers)
{   
    char input[NAME_LENGTH];

    printf("Введите имя абонента, которого вы хотите найти.\n");
    scanf("%s", input);

    for (uint16_t i; i < num_subscribers; i++) {
        if (strcmp(phonebook[i].name, input) == 0) {
            printf("%s %s %s\n", phonebook[i].name, phonebook[i].surname, phonebook[i].phone_number);
        }
    }
    return;
}