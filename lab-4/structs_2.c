/**
 * Лабораторная 4. Задание 2.
 *
 * structs_2.c -- программа, реализующая телефонный справочник с помощью структур.
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

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
struct subscriber {
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    char phone_number[PHONE_NUMBER_LENGTH];
};

/* Функция, выводящая пункты меню */
void print_menu();

/* Добавить абонента */
void add_subscriber(struct subscriber phonebook[], uint16_t* num_subscribers, uint8_t vacant_space[]);

/* Вывести всех абонентов */
void print_all_subscribers(struct subscriber phonebook[]);

/* Удалить абонента */
void delete_subscriber(struct subscriber phonebook[], uint16_t* num_subscribers, uint8_t vacant_space[]);

/* Найти абонента и вывести его */
void find_subscriber(struct subscriber phonebook[]);

int main()
{
    struct subscriber phonebook[PHONEBOOK_LENGTH] = {0};    // Массив абонентов
    uint8_t vacant_space[PHONEBOOK_LENGTH] = {0};             // Массив, показывающий свободные места в справочнике
    uint16_t option = 0;                                      // Опция, выбранная пользователем
    uint16_t num_subscribers = 0;                             // Количество абонентов в справочнике 

    while (1) {
        print_menu();
        printf("Введите выбранную опцию:\n");
        scanf("%hu", &option);                  // Считываем опцию, выбранную пользователем
        switch(option) {
            case ADD:
                /* Если справочник не заполнен, то добавляем абонента */
                if (num_subscribers < PHONEBOOK_LENGTH) {
                    add_subscriber(phonebook, &num_subscribers, vacant_space);
                } else {
                    printf("В справочнике нет свободного места!\n");
                    continue;
                }
                break;
            case SHOW:
                print_all_subscribers(phonebook);
                break;
            case DELETE:
                delete_subscriber(phonebook, &num_subscribers, vacant_space);
                break;
            case FIND:
                find_subscriber(phonebook);
                break;
            case EXIT:
                exit(EXIT_SUCCESS);
        }       
    }
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
void add_subscriber(struct subscriber phonebook[], uint16_t* num_subscriber, uint8_t vacant_space[])
{
    /* Ищем первое свободное место */
    uint8_t index = 0;
    for (uint16_t i = 0; i < PHONEBOOK_LENGTH; i++) {
        if(vacant_space[i] == 0) {
            index = i;
            break;
        }
    }

    printf("Введите данные нового абонента.\n");
    scanf("%s", phonebook[index].name);
    scanf("%s", phonebook[index].surname);
    scanf("%s", phonebook[index].phone_number);

    vacant_space[index] = 1;
    *num_subscriber = *num_subscriber + 1;
    return;
}

/* Вывести всех абонентов */
void print_all_subscribers(struct subscriber phonebook[])
{
    for (uint16_t i = 0; i < PHONEBOOK_LENGTH; i++) {
        if ((phonebook[i].name[0] != '0') && (phonebook[i].surname[0] != '0')) {
            printf("%s %s %s\n", phonebook[i].name, phonebook[i].surname, phonebook[i].phone_number);
        }
    }
    return;
}

/* Удалить абонента */
void delete_subscriber(struct subscriber phonebook[], uint16_t* num_subscribers, uint8_t vacant_space[])
{
    char input[NAME_LENGTH];

    printf("Введите имя абонента, которого вы хотите удалить.\n");
    scanf("%s", input);

    for (uint16_t i = 0; i < PHONEBOOK_LENGTH; i++) {
        if (strcmp(phonebook[i].name, input) == 0) {
            /* Зануляем имя и фамилию */
            for (uint16_t j = 0; j < NAME_LENGTH; j++) {
                phonebook[i].name[j] = '0';
                phonebook[i].surname[j] = '0';
            }
            /* Зануляем телефон */
            for (uint16_t k = 0; k < PHONE_NUMBER_LENGTH; k++) {
                phonebook[i].phone_number[k] = '0';
            }
            vacant_space[i] = 0;
            *num_subscribers = *num_subscribers - 1;
            break;
        }
    }

    return;
}

/* Найти абонента и вывести его */
void find_subscriber(struct subscriber phonebook[])
{   
    char input[NAME_LENGTH];

    printf("Введите имя абонента, которого вы хотите найти.\n");
    scanf("%s", input);

    for (uint16_t i = 0; i < PHONEBOOK_LENGTH; i++) {
        if (strcmp(phonebook[i].name, input) == 0) {
            printf("%s %s %s\n", phonebook[i].name, phonebook[i].surname, phonebook[i].phone_number);
        }
    }
    return;
}
