/**
 * Лабораторная 9. Задание 1.
 *
 * calculator.c -- главный файл программы-калькулятора. (Версия с плагинами)
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include "func_info.h"

/* Указатель на ф-ию, выполянющую к-л арифметическую операцию (Необходимо для массива функций) */
typedef void (*func)(void);

/* Структура, хранящая информацию об обнаруженных плагинах */
struct libs_info
{
    char **libs_names;   // Массив, в который добавляются имена плагинов, к-е будут подключаться
    uint16_t num_libs;   // Количество плагинов, обнаруженных в директории
};

/* Структура, хранящая информацию о подключённых DSO, функциях и их описаниях */
struct pluged_in_funcs
{
    void **DSO_array;       // Массив из указателей на dynamic shared object (DSO)
    func *funcs_array;      // Массив указателей на функции, которые были подключены из DSO
    char **descriptions;    // Массив описаний действий, которые воплняет каждая функция (Для меню)
    uint8_t num_of_funcs;   // Количество подключённых функций
};

/* Функция, ищущая плагины в директории */
struct libs_info *find_plugins();

/* Функция, к-я подключает плагины. */
struct pluged_in_funcs *add_plugins(struct libs_info *libs);

/* Функция, выводящая пункты меню */
void print_menu(struct pluged_in_funcs *funcs);

/* Функция, очищающая память */
void free_memory(struct libs_info *libs, struct pluged_in_funcs *funcs);

int main()
{
    uint8_t option = 0;                     // Опция, выбранная пользователем
    struct libs_info *libs = NULL;          // Стр-ра для инф-ии об обнаруженных библиотеках
    struct pluged_in_funcs *funcs = NULL;   // Стр-ра для инф-ии о подключённых ф-ях

    /* Ищем динамические бибилиотеки */
    libs = find_plugins();
    /* Подключаем функции */
    funcs = add_plugins(libs);
    /* Если не было подключено ни одной функции, то завершаем работу */
    if (funcs->num_of_funcs == 0) {
        fprintf(stderr, "%s", "No plugins found!\n");
        exit(EXIT_FAILURE);
    }

    /* Обработка пользовательского ввода */
    while (1) {
        print_menu(funcs);
        /* Считываем опцию, выбранную пользователем */
        printf("Enter the selected option:\n");
        scanf("%hhu", &option);

        /* Проверяем, корректна ли введённая пользователем опция */
        if (option <= funcs->num_of_funcs) {
            /* Если опция это номер к-н арифметической операции, то вызываем соответсвующую функцию */
            if (option != funcs->num_of_funcs) {
                func f = funcs->funcs_array[option];
                f();
            /* Иначе была пользователь ввёл опцию для выходя из программы */
            } else {
                free_memory(libs, funcs);
                exit(EXIT_SUCCESS);
            }
        /* Если опция некорректна, то выводим об этом сообщение */
        } else {
            fprintf(stderr, "%s", "Unknown option!\n");
            continue;
        }
    }

    exit(EXIT_SUCCESS);
}

/* Функция, ищущая плагины в директории plugins */
struct libs_info *find_plugins()
{
    DIR *dirp = NULL;              // Директория, где хранятся плагины
    struct dirent *file = NULL;    // Структура, в к-ю будет записываться инф-ия о файлах в директории

    /* Создаём структуру, которая будет хранить инф-ию об обнаруженных библиотеках */
    struct libs_info *libs = (struct libs_info *) malloc(sizeof(struct libs_info)); 
    libs->libs_names = NULL;
    libs->num_libs = 0;

    /* Открываем директорию plugins */
    if ((dirp = opendir("plugins")) == NULL) {
        perror("Failed to open dir");
        exit(EXIT_FAILURE);        
    }

    /* Проходим по директории */
    while ((file = readdir(dirp)) != NULL) {
        /* Пропускаем "." и ".." */
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }

        /* Пропускаем файлы, в именах к-х нет ".so" */
        if (strstr(file->d_name, ".so") == NULL) {
            continue;
        }

        /* Выделение памяти для записи имени библиотеки, которая обнаружена */
        libs->num_libs = libs->num_libs + 1;
        libs->libs_names = (char **) realloc(libs->libs_names, sizeof(char *) * libs->num_libs);
        libs->libs_names[libs->num_libs - 1] = (char *) malloc(strlen(file->d_name) * sizeof(char));

        /* Записываем имя библиотеки */
        strcpy(libs->libs_names[libs->num_libs - 1], file->d_name);
    }

    /* Если при обхода была ошибка, то сообщаем об этом и выходим из программы */
    if (errno != 0) {
        perror("Failed to read dir");
        exit(EXIT_FAILURE);
    }
    
    return libs;
}

struct pluged_in_funcs *add_plugins(struct libs_info *libs)
{
    /* Создаём структуру для хранения информации о функциях, которые будут подключены */
    struct pluged_in_funcs *funcs = (struct pluged_in_funcs *) malloc(sizeof(struct pluged_in_funcs));
    funcs->DSO_array = (void **) malloc(sizeof(void *) * libs->num_libs);
    funcs->descriptions = (char **) malloc(sizeof(char *) * libs->num_libs);
    funcs->funcs_array = (func *) malloc(sizeof(func) * libs->num_libs);
    funcs->num_of_funcs = 0;

    void *DSO = NULL;            // Указатель на dynamic shared object (DSO)
    func function = NULL;        // Указатель на функцию из DSO
    struct func_info *f_info;    // Указатель на структуру, содержащую информацию о функции

    /* Переменная для хранения пути к плагину */
    char *plugin_path = (char *) malloc(sizeof(char) * PATH_MAX);
    strcpy(plugin_path, "plugins/");
    int32_t plugin_path_init_len = strlen(plugin_path);

    /* Переменная для хранения строки с названием структуры, где хранится информация о функции */
    char *func_info_struct_name = (char *) malloc(sizeof(char) * PATH_MAX);
    strcpy(func_info_struct_name, "func_info_");
    int32_t func_info_struct_name_init_len = strlen(func_info_struct_name);

    /* Обрабатываем массив имён обнаруженных бибилиотек */
    for (uint16_t i = 0; i < libs->num_libs; i++) {
        /* Конструируем путь до бибилиотеки */
        strcat(plugin_path, libs->libs_names[i]);

        /* Подключаем библиотеку */
        DSO = dlopen(plugin_path, RTLD_LAZY);
        /* Если не удалось подключить библиотеку, то выходим из программы */
        if (DSO == NULL) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        /* Записываем название структуры, в которой хранится информация о функции */
        strcat(func_info_struct_name, libs->libs_names[i]);
        /* Отсекаем расширение ".so" */
        func_info_struct_name[strlen(func_info_struct_name) - 3] = '\0';

        /* Находим структуру с информацией о функции */
        f_info = (struct func_info *) dlsym(DSO, func_info_struct_name);
        /* Если не обнаружена структура, то отключаем этот DSO */
        if (f_info == NULL) {
            /* Возвращаем строку для пути и строку для названия структуры к исходному виду */
            plugin_path[plugin_path_init_len] = '\0';
            func_info_struct_name[func_info_struct_name_init_len] = '\0';
            dlclose(DSO);
            continue;
        }

        /* Находим функцию по имени */
        function = (func) dlsym(DSO, f_info->func_name);
        
        /* Добавляем информацию в структуру funcs */
        funcs->DSO_array[funcs->num_of_funcs] = DSO;
        funcs->funcs_array[funcs->num_of_funcs] = function;
        funcs->descriptions[funcs->num_of_funcs] = (char *) malloc(sizeof(char) * PATH_MAX);
        strcpy(funcs->descriptions[funcs->num_of_funcs], f_info->func_description);
        funcs->num_of_funcs = funcs->num_of_funcs + 1;

        /* Возвращаем строку пути и строку названия структуры к исходному виду */
        plugin_path[plugin_path_init_len] = '\0';
        func_info_struct_name[func_info_struct_name_init_len] = '\0';
    }

    /* Если были найдены функции, которые были подключены */
    if (funcs->num_of_funcs > 0) {
        /* Уменьшаем размер динамических массивов до фактически использованного размера */
        funcs->DSO_array = (void **) realloc(funcs->DSO_array, sizeof(void *) * funcs->num_of_funcs);
        funcs->funcs_array = (func *) realloc(funcs->funcs_array, sizeof(func) * funcs->num_of_funcs);
        funcs->descriptions = (char **) realloc(funcs->descriptions, sizeof(char *) * funcs->num_of_funcs);
    }

    return funcs;
}

/* Функция, выводящая пункты меню */
void print_menu(struct pluged_in_funcs *funcs)
{   
    printf("============================\n");
    printf("Simple calculator.\n");
    printf("Menu:\n");
    uint32_t i = 0;
    while (i < funcs->num_of_funcs) {
        printf("%i -- %s\n", i, funcs->descriptions[i]);
        i++;
    }
    printf("%i -- %s\n", i, "Exit.");

    return;
}

/* Функция, очищающая память */
void free_memory(struct libs_info *libs, struct pluged_in_funcs *funcs)
{
    /* Отчистка структуры libs */
    for (uint32_t i = 0; i < libs->num_libs; i++) {
        free(libs->libs_names[i]);
    }
    free (libs);

    /* Отчистка структуры funcs */
    for (uint32_t i = 0; i < funcs->num_of_funcs; i++) {
        free(funcs->descriptions[i]);
        dlclose(funcs->DSO_array[i]);
    }
    free(funcs->DSO_array);
    free(funcs->funcs_array);
    free(funcs);

    return;
}
