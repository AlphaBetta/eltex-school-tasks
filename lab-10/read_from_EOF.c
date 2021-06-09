/**
 * Лабораторная 10. Задание 1.
 *
 * read_from_EOF.c -- читает строку с конца из файла
 *
 * Copyright (c) 2021, Ruslan Sergeev <ruslansergeew@yandex.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STR_LEN 9
#define STR "ABCDEFG\n"

int main()
{
    int fd = 0;                 // Файловый дескриптор открытого файла
    char str[STR_LEN] = {0};    // Буфер, куда будет записана строка из файла

    /* Открываем файл, куда будет записана строка */
    if ((fd = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    /* Записываем строку в файл */
    if (write(fd, STR, STR_LEN) == -1) {
        perror("Failed to write data");
        exit(EXIT_FAILURE);
    }

    /* Закрываем файл */
    if (close(fd) == -1) {
        perror("Failde to close file");
        exit(EXIT_FAILURE);
    }

    /* Снова открываем файл */
    if ((fd = open("test.txt", O_RDONLY)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int offset = STR_LEN - 1;
    int file_position = 0;

    while (offset >= 0) {
        /* Перемещаемся соответствующую позицию в файле */
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("Failed to seek end");
            exit(EXIT_FAILURE);
        }

        if (offset > STR_LEN - 3) {
            /* Читаем из файла первые два символа с конца и записываем в конец буфера ('\n' и '\0') */
            if (read(fd, &str[offset], 1) == -1) {
                perror("Failed to read data");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Читаем из файла и записываем в начало буфера (Все остальные символы) */
            if (read(fd, &str[file_position], 1) == -1) {
                perror("Failed to read data");
                exit(EXIT_FAILURE);
            }
            file_position = file_position + 1;
        }

        offset = offset - 1;
    } 

    printf("%s", str);

    exit(EXIT_SUCCESS);
}