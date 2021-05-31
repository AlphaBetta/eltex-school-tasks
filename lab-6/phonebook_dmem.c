/**
 * Лабораторная 6. Задание 1.
 *
 * phonebook_dmem.c -- программа, реализующая телефонный справочник с помощью структур. 
 * (Версия с использованием динамического выделения памяти)
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NAME_LENGTH 100
#define PHONE_NUMBER_LENGTH 13

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

    struct subscriber *next;    // Указатель на следующего абонента
    struct subscriber *prev;    // Указатель на предыдущего абонента
};

/* Структура справочника */
struct phonebook {
    struct subscriber *head;    // Указатель на первого абонента в справочнике
    struct subscriber *tail;    // Указатель на последнего абонента в справочнике
    uint16_t num_subscribers;   // Количество абонентов в справочнике
};

/* Функция, выводящая пункты меню */
void print_menu();

/* Добавить абонента */
void add_subscriber(struct phonebook *phonebook);

/* Вывести всех абонентов */
void print_all_subscribers(struct phonebook *phonebook);

/* Удалить абонента */
void delete_subscriber(struct phonebook *phonebook);

/* Найти абонента и вывести его */
void find_subscriber(struct phonebook *phonebook);

int main()
{
    /* Структура справочника */
    struct phonebook *phonebook = (struct phonebook *) malloc(sizeof(struct phonebook));     
    phonebook->head = NULL;
    phonebook->tail = NULL;
    phonebook->num_subscribers = 0;

    uint16_t option = 0;    // Опция, выбранная пользователем

    while (1) {
        print_menu();
        printf("Введите выбранную опцию:\n");
        scanf("%hu", &option);    // Считываем опцию, выбранную пользователем
        switch(option) {
            case ADD:
                add_subscriber(phonebook);
                break;
            case SHOW:
                print_all_subscribers(phonebook);
                break;
            case DELETE:
                delete_subscriber(phonebook);
                break;
            case FIND:
                find_subscriber(phonebook);
                break;
            case EXIT:
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("%s", "Неизвестная опция!\n");
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
void add_subscriber(struct phonebook *phonebook)
{
    struct subscriber *new_subscriber = (struct subscriber *) malloc(sizeof(struct subscriber));
    new_subscriber->next = NULL;
    new_subscriber->prev = NULL;    

    printf("Введите данные нового абонента.\n");
    scanf("%s", new_subscriber->name);
    scanf("%s", new_subscriber->surname);
    scanf("%s", new_subscriber->phone_number);

    /* Если справочник пуст */
    if ((phonebook->head == NULL) && (phonebook->tail == NULL)) {
        phonebook->head = new_subscriber;
        phonebook->tail = new_subscriber;
    /* Если справочник не пуст */
    } else {
        new_subscriber->prev = phonebook->tail;
        phonebook->tail->next = new_subscriber;
        phonebook->tail = new_subscriber;
    }

    phonebook->num_subscribers++;

    return;
}

/* Вывести всех абонентов */
void print_all_subscribers(struct phonebook *phonebook)
{   
    if (phonebook->num_subscribers > 0) {
        struct subscriber *cur_subscriber = phonebook->head; 
        for (int i = 0; i < phonebook->num_subscribers; i++) {
            printf("%s %s %s\n", cur_subscriber->name,
                                 cur_subscriber->surname,
                                 cur_subscriber->phone_number);
            cur_subscriber = cur_subscriber->next;
        } 
    } else {
        printf("%s", "Справочник пуст!\n");
    }

    return;
}

/* Удалить абонента */
void delete_subscriber(struct phonebook *phonebook)
{

    return;
}

/* Найти абонента и вывести его */
void find_subscriber(struct phonebook *phonebook)
{   
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];

    printf("Введите имя абонента, которого вы хотите найти.\n");
    scanf("%s", name);
    printf("Введите фамилию абонента, которого вы хотите найти.\n");
    scanf("%s", surname);

    struct subscriber *cur_subscriber = phonebook->head;
    for (int i = 0; i < phonebook->num_subscribers; i++) {
        if ((strcmp(cur_subscriber->name, name) == 0) && 
            (strcmp(cur_subscriber->surname, surname) == 0)) {
            printf("%s %s %s\n", cur_subscriber->name, cur_subscriber->surname, cur_subscriber->phone_number);
            break;
        } else {
            cur_subscriber = cur_subscriber->next;
        }
    }

    printf("%s", "В справочнике не найден абонент с такими именем и фамилией!\n");
    return;
}
