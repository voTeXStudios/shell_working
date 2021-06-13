#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include "cat.h"

#define Buffer_size 512

// if -E and -n option
void rewrite(int fd_in, int fd_out, char *buf, int count, int e_triggered, int* n, int n_triggered)
{
    int i = 0;
    int printed;
    int w;
    while (1)
    {
        if (i == count)
            break;
        w = write(fd_out, &buf[i], 1);

        if (w == -1)
        {
           fprintf(stderr, "Error while writing\n");
           break;
        }

        if (w == 0)
            break;

        if (buf[i] == '\n' && n_triggered == 1 && fd_in != STDIN_FILENO){
            char number_str[50];
            printed = sprintf(number_str, "  %d  ", *n);
            if (write(fd_out, number_str, printed) == -1){
                fprintf(stderr, "Error while writing the line number\n");
                break;
            }
            *n += 1;
        }

        if (buf[i + 1] == '\n' && e_triggered == 1)
        {
            if (write(fd_out, "$", 1) == -1){
               fprintf(stderr, "Error while writing $ symbol\n");
               break;
            }
        }

        i += 1;
    }

}

void re_read(int fd_out, int fd_in, int e_triggered, int* n, int n_triggered)
{
    char buffer[Buffer_size];
    int r;
    int printed;

    if (fd_in != STDIN_FILENO && n_triggered == 1)
    {
        char number_str[50];
        printed = sprintf(number_str, "  %d  ", *n);
        if (write(fd_out, number_str, printed) == -1){
            fprintf(stderr,"Error while writing the line number\n");
            return;
        }
        *n += 1;
    }

    while (1)
    {
        r = read(fd_in, buffer, Buffer_size);
        if (r == 0)
            break;
        if (r == -1)
        {
            fprintf(stderr,"Error while reading\n");
            return;
        }
        if (fd_in == STDIN_FILENO && n_triggered == 1)
        {
            char number_str[50];
            printed = sprintf(number_str, "  %d  ", *n);
            if (write(fd_out, number_str, printed) == -1)
            {
                fprintf(stderr,"Error while writing the line number\n");
                return;
            }
            *n += 1;
        }
        rewrite(fd_in, fd_out, buffer, r, e_triggered, n, n_triggered);
    }
}

void check_flags(int argc, char* argv[], int* e_triggered, int* n_triggered, int* file_exists)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-E", argv[i]) == 0)
            *e_triggered = 1;
        else if (strcmp("-n", argv[i]) == 0)
            *n_triggered = 1;
        else if (strcmp("-", argv[i]) == 0)
            continue;
        else
            *file_exists = 1;
    }
}

void _cat(int argc, char *argv[])
{
    int e_triggered = 0;
    int fd_in;
    int n_triggered = 0;
    int n = 1;
    int file_exists = 0;
    // Just cat command
    if (argc < 2)
    {
        re_read(STDOUT_FILENO, STDIN_FILENO, 0, &n, 0);
        return;
    }

    check_flags(argc, argv, &e_triggered, &n_triggered, &file_exists);
    if (file_exists == 0){
        re_read(STDOUT_FILENO, STDIN_FILENO, e_triggered, &n, n_triggered);
        return;
    }

    // Main loop that calls cat
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-E", argv[i]) != 0 && strcmp("-n",argv[i]) != 0 && strcmp("-", argv[i]) != 0)
        {
            fd_in = open(argv[i], O_RDONLY);
            if (fd_in == -1)
            {
                fprintf(stderr, "Invalid Operand: Either file does not exists or invalid flag\n. Type 'help' to know more\n");
                return;
            }

            re_read(STDOUT_FILENO, fd_in, e_triggered, &n, n_triggered);
            if (i != argc - 1){
                if (write(STDOUT_FILENO, "\n", 2) == -1)
                {
                    fprintf(stderr,"Error while writing next line\n");
                    return;
                }
            }
        }
        else if (strcmp("-", argv[i]) == 0)
            re_read(STDOUT_FILENO, STDIN_FILENO, e_triggered, &n, n_triggered);
    }
    return;
}
