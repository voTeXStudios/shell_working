#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "functions.h"
#include <dirent.h>
#include "cd.h"
#include "functions.h"
#include "ls.h"
#include "cat.h"
#include "tree.h"
#include "hostname.h"
#include "grep.h"
#include "echo.h"

void redirection(char *buf, int type)
{
    char *op[2];
    char *ip[2];
    char *temp;
    char *temp2;

    char** st = malloc(100 * sizeof(char*));
    for (size_t i = 0; i < 100; i++)
      st[i] = calloc(100, sizeof(char));
    int i, k = 0, pid, status, in, out;

    op[0] = strtok(buf, ">");
    op[1] = strtok(NULL, ">");

    ip[0] = strtok(op[0], "<");
    ip[1] = strtok(NULL, "<");

    temp = strtok(ip[0], " \n\t\r");
    while (temp != NULL)
    {
        strcpy(st[k++], temp);
        temp = strtok(NULL, " \n\t\r");
    }

    char *com[k + 1];
    for (i = 0; i < k; i++)
        com[i] = st[i];

    com[i] = NULL;

    pid = fork();
    if (ip[1] != NULL)
    {
        temp2 = strtok(ip[1], " \n\t\r");
        if (temp2 != NULL)
        {
            in = open(temp2, O_RDONLY);
            if (pid == 0)
            {
                if (in >= 0)
                    dup2(in, STDIN_FILENO);
                else
                {
                    printf("File does not exist\n");
                    return;
                }
            }
        }
        else
        {
            if (pid == 0)
            {
                printf("Invalid input file\n");
                exit(0);
            }
        }
    }
    if (op[1] != NULL)
    {
        temp2 = strtok(op[1], " \n\t\r");
        if (temp2 != NULL)
        {
            if (type == 0)
                out = open(temp2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            else
                out = open(temp2, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            if (pid == 0)
            {
                dup2(out, STDOUT_FILENO);
            }
        }
        else
        {
            if (pid == 0)
            {
                printf("Invalid output file\n");
                exit(0);
            }
        }
    }
    if (pid == 0)
    {
        char *token;
        token = strtok(com[0], " \n\t\r");
        if (strcmp(token, "cd") == 0)
            cd(k, st);
        else if (strcmp(token, "pwd") == 0)
            pwd(k);
        else if (strcmp(token, "ls") == 0)
            _ls(k, st);
        else if (strcmp(token, "cat") == 0)
            _cat(k, st);
        else if (strcmp(token, "tree") == 0)
            _tree(k, st);
        else if (strcmp(token, "hostname") == 0)
            get_host_name(k, st);
        else if (strcmp(token, "grep") == 0)
            grep(k, st);
        else if (strcmp(token, "echo") == 0)
            echo(st, k);
        /*else if (strcmp(token, "help") == 0)
            helppage(k);*/
        else if (strcmp(token, "mkdir") == 0)
            create_dir(k, st);
        exit(0);
    }
    else
    {
        while (wait(&status) != pid)
            ;
    }
    free(st);
    return;


}
