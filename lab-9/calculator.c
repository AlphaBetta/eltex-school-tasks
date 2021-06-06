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

/* Указатель на ф-ию (Необходимо для массива функций) */
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
    void **DSO_array;       // Массив из dynamic shared object (DSO)
    func *funcs_array;      // Массив указателей на функции, которые были подключены из DSO
    char **descriptions;     // Массив описаний действий, которые воплняет каждая функция (Для меню)
    uint8_t num_of_funcs;   // Количество подключённых функций
};

/* Функция, ищущая плагины в директории */
struct libs_info *find_plugins();

/* Функция, к-я подключает плагины. */
struct pluged_in_funcs *add_plugins(struct libs_info *libs);

/* Функция, выводящая пункты меню */
void print_menu(struct pluged_in_funcs *functions);

/* Функция, очищающая память */
void free_memory(struct libs_info *libs, struct pluged_in_funcs *functions);

int main()
{
    uint8_t option = 0;    // Опция, выбранная пользователем

    struct libs_info *libs = find_plugins();
    struct pluged_in_funcs *functions = add_plugins(libs);
    if (functions->num_of_funcs == 0) {
        fprintf(stderr, "%s", "No plugins found!\n");
        exit(EXIT_FAILURE);
    }

    /* Обработка пользовательского ввода */
    while (1) {
        print_menu(functions);
        printf("Enter the selected option:\n");
        scanf("%hhu", &option);    // Считываем опцию, выбранную пользователем
        /* Проверяем, существует ли опция с таким номером */
        if (option > functions->num_of_funcs) {
            fprintf(stderr, "%s", "Unknown option!\n");
            continue;
        /* Обрабатываем опцию в соответсвие с её номером */
        } else {
            /* Если опция отвечает за номер ф-ии, то вызываем её */
            if (option != functions->num_of_funcs) {
                func f = functions->funcs_array[option];
                f();
            } else {
                /* Иначе -- выходим из программы */
                free_memory(libs, functions);
                exit(EXIT_SUCCESS);
            }
        }
    }
    


    exit(EXIT_SUCCESS);
}

/* Функция, ищущая плагины в директории plugins */
struct libs_info *find_plugins()
{
    DIR *dirp = NULL;           // Директория, где хранятся плагины
    struct dirent *file;        // Структура для хранения информации о файлах в директории при её чтении

    /* Структура, которая хранит информацию об обнаруженных библиотеках */
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

    /* Если при обхода была ошибка, то сообщаем об этом и выходим */
    if (errno != 0) {
        perror("Failed to read dir");
        exit(EXIT_FAILURE);
    }
    
    return libs;
}

struct pluged_in_funcs *add_plugins(struct libs_info *libs)
{
    /* Структура ф-й, которые были подключены */
    struct pluged_in_funcs *funcs = (struct pluged_in_funcs *) malloc(sizeof(struct pluged_in_funcs));
    funcs->DSO_array = (void **) malloc(sizeof(void *) * libs->num_libs);
    funcs->descriptions = (char **) malloc(sizeof(char *) * libs->num_libs);
    funcs->funcs_array = (func *) malloc(sizeof(func) * libs->num_libs);
    funcs->num_of_funcs = 0;

    void *DSO = NULL;                   // Указатель на dynamic shared object (DSO)
    func function = NULL;               // Указатель на функцию из DSO
    struct func_info *function_info;    // Указатель на структуру, содержащую информацию о функции

    /* Переменная для хранения пути к плагину */
    char *plugin_path = (char *) malloc(sizeof(char) * PATH_MAX);
    strcpy(plugin_path, "plugins/");
    int32_t plugin_path_inicial_length = strlen(plugin_path);

    /* Переменная для хранения названия структуры, где хранится информация о функции */
    char *func_info_struct_name = (char *) malloc(sizeof(char) * PATH_MAX);
    strcpy(func_info_struct_name, "func_info_");
    int32_t func_info_struct_name_inicial_length = strlen(func_info_struct_name);

    /* Обрабатываем массив имён обнаруженных бибилиотек */
    for (uint16_t i = 0; i < libs->num_libs; i++) {
        strcat(plugin_path, libs->libs_names[i]);   // Записываем путь к библиотеке

        DSO = dlopen(plugin_path, RTLD_LAZY);
        /* Если не удалось подключить библиотеку */
        if (DSO == NULL) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        /* Записываем название структуры, в которой хранится информация о функции */
        strcat(func_info_struct_name, libs->libs_names[i]);
        func_info_struct_name[strlen(func_info_struct_name) - 3] = '\0';

        /* Находим структуру с информацией о функции */
        function_info = (struct func_info *) dlsym(DSO, func_info_struct_name);
        /* Если не обнаружена структура, то отключаем этот DSO */
        if (function_info == NULL) {
            /* Возвращаем строку пути и строку названия структуры к исходному виду */
            plugin_path[plugin_path_inicial_length] = '\0';
            func_info_struct_name[func_info_struct_name_inicial_length] = '\0';
            dlclose(DSO);
            continue;
        }

        /* Находим функцию по имени */
        function = (func) dlsym(DSO, function_info->func_name);
        
        /* Добавляем информацию в структуру funcs */
        funcs->DSO_array[funcs->num_of_funcs] = DSO;
        funcs->funcs_array[funcs->num_of_funcs] = function;
        funcs->descriptions[funcs->num_of_funcs] = (char *) malloc(sizeof(char) * PATH_MAX);
        strcpy(funcs->descriptions[funcs->num_of_funcs], function_info->func_description);
        funcs->num_of_funcs = funcs->num_of_funcs + 1;

        /* Возвращаем строку пути и строку названия структуры к исходному виду */
        plugin_path[plugin_path_inicial_length] = '\0';
        func_info_struct_name[func_info_struct_name_inicial_length] = '\0';
    }

    if (funcs->num_of_funcs > 0) {
        /* Уменьшаем размер динамических массивов до фактически использованного размера */
        funcs->DSO_array = (void **) realloc(funcs->DSO_array, sizeof(void *) * funcs->num_of_funcs);
        funcs->funcs_array = (func *) realloc(funcs->funcs_array, sizeof(func) * funcs->num_of_funcs);
        funcs->descriptions = (char **) realloc(funcs->descriptions, sizeof(char *) * funcs->num_of_funcs);
    }

    return funcs;
}

/* Функция, выводящая пункты меню */
void print_menu(struct pluged_in_funcs *functions)
{   
    printf("============================\n");
    printf("Simple calculator.\n");
    printf("Menu:\n");
    uint32_t i = 0;
    while (i < functions->num_of_funcs) {
        printf("%i -- %s\n", i, functions->descriptions[i]);
        i++;
    }
    printf("%i -- %s\n", i, "Exit.");

    return;
}

/* Функция, очищающая память */
void free_memory(struct libs_info *libs, struct pluged_in_funcs *functions)
{
    /* Отчистка структуры libs */
    for (uint32_t i = 0; i < libs->num_libs; i++) {
        free(libs->libs_names[i]);
    }
    free (libs);

    /* Отчистка структуры functions */
    for (uint32_t i = 0; i < functions->num_of_funcs; i++) {
        free(functions->descriptions[i]);
        dlclose(functions->DSO_array[i]);
    }
    free(functions->DSO_array);
    free(functions->funcs_array);
    free(functions);

    return;
}
