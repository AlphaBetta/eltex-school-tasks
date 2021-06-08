/**
 * Лабораторная 9. Задание 1.
 *
 * func_info.h -- Заголовочный файл, хранящий описание структуры.
 * В структуре -- информация для корректной работы с функцией в плагине. 
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#define PATH_MAX 256

/* Структура, хранящая информацию о функции, к-я подключается к калькулятору */
struct func_info
{
    char func_name[PATH_MAX];         // Имя ф-ии (Совпадает с именем в коде)
    char func_description[PATH_MAX];  // Описание действия, к-е выполняет ф-я (Необходимо для формирования меню)
};
