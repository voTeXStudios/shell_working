#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "functions.h"
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include "pipe.h"
#include "cd.h"
#include "functions.h"
#include "ls.h"
#include "cat.h"
#include "tree.h"
#include "hostname.h"
#include "grep.h"
#include "echo.h"


int check_op(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>')
            return 1;
        i++;
    }
    return 0;
}

int check_ip(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<')
            return 1;
        i++;
    }
    return 0;
}

void execute_pipe(char *buff)
{
    char ***commands = (char ***)malloc(sizeof(char **) * 50);
    char *com;
    char *end;
    int num_com = 0;
    com = strtok_r(buff, "|", &end);
    int i = 0, j;
    while (com != NULL)
    {
        j = 0;
        char *token;
        char *end_tok;
        commands[i] = (char **)malloc(sizeof(char *) * 50);
        token = strtok_r(com, " \n\t\r", &end_tok);
        while (token != NULL)
        {
            commands[i][j] = (char *)malloc(sizeof(char) * 50);
            strcpy(commands[i][j], token);
            token = strtok_r(NULL, " \n\t\r", &end_tok);
            j++;
        }
        commands[i][j] = NULL;
        num_com++;
        com = strtok_r(NULL, "|", &end);
        i++;
    }
    commands[i] = NULL;

    int p = 0;
    int fd[2];
    int fd_in = 0;
    pid_t pid;

    while (*commands != NULL)
    {
        pipe(fd);
        pid = fork();
        int saved_stdout = dup(STDOUT_FILENO);

        if (pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0);
            if (p != (num_com - 1))
                dup2(fd[1], 1);
            close(fd[0]);
            if (check_ip((*commands)[0]))
            {
                char *ip[2];
                char *temp;
                char** st = malloc(100 * sizeof(char*));
                for (size_t i = 0; i < 100; i++)
                    st[i] = calloc(100, sizeof(char));
                int k = 0;
                ip[0] = strtok((*commands)[0], "<");
                ip[1] = strtok(NULL, "<");

                temp = strtok(ip[0], " \n\t\r");
                while (temp != NULL)
                {
                    strcpy(st[k++], temp);
                    //printf("%s\n", temp);
                    temp = strtok(NULL, " \n\t\r");
                }

                char *cmd[k + 1];
                for (i = 0; i < k; i++)
                    cmd[i] = st[i];
                cmd[i] = NULL;

                char *t = strtok(ip[1], " \n\t\r");
                if (t != NULL)
                {
                    int in = open(t, O_RDONLY);
                    if (in < 0)
                    {
                        printf("File does not exist\n");
                        return;
                    }
                    else
                        dup2(in, 0);
                }
                char *token;
                token = strtok(cmd[0], " \n\t\r");
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
                else if (strcmp(token, "rmdir") == 0)
                    remove_dir(k, st);
                else if (strcmp(token, "tictactoe") == 0)
                    play(k);
                else if (strcmp(token, "mv") == 0)
                    mv(k, st);
                else if (strcmp(token, "calc") == 0)
                    calc(k);
                else
                {
                    dup2(saved_stdout, 1);
                    printf("No such Command.\n");
                }
                free(st);
            }
            if (check_op((*commands)[0]))
            {
                char *op[2];
                char *temp;
                char** st = malloc(100 * sizeof(char*));
                for (size_t i = 0; i < 100; i++)
                    st[i] = calloc(100, sizeof(char));
                int k = 0;
                op[0] = strtok((*commands)[0], ">");
                op[1] = strtok(NULL, ">");

                temp = strtok(op[0], " \n\t\r");
                while (temp != NULL)
                {
                    strcpy(st[k++], temp);
                    //printf("%s\n", temp);
                    temp = strtok(NULL, " \n\t\r");
                }

                char *cmd[k + 1];
                for (i = 0; i < k; i++)
                    cmd[i] = st[i];
                cmd[i] = NULL;

                char *t = strtok(op[1], " \n\t\r");
                if (t != NULL)
                {
                    int out = open(t, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    dup2(out, 1);

                    char *token;
                    token = strtok(cmd[0], " \n\t\r");
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
                    else if (strcmp(token, "rmdir") == 0)
                        remove_dir(k, st);
                    else if (strcmp(token, "tictactoe") == 0)
                        play(k);
                    else if (strcmp(token, "mv") == 0)
                        mv(k, st);
                    else if (strcmp(token, "calc") == 0)
                        calc(k);
                    else
                    {
                        dup2(saved_stdout, 1);
                        printf("No such Command.\n");
                    }
                    free(st);
                }
            }
            else
            {
                char *token;
                token = strtok((*commands)[0], " \n\t\r");
                if (strcmp(token, "cd") == 0)
                    cd(j, (*commands));
                else if (strcmp(token, "pwd") == 0)
                    pwd(j);
                else if (strcmp(token, "ls") == 0)
                    _ls(j, (*commands));
                else if (strcmp(token, "cat") == 0)
                    _cat(j, (*commands));
                else if (strcmp(token, "tree") == 0)
                    _tree(j, (*commands));
                else if (strcmp(token, "hostname") == 0)
                    get_host_name(j, (*commands));
                else if (strcmp(token, "grep") == 0)
                    grep(j, (*commands));
                else if (strcmp(token, "echo") == 0)
                    echo((*commands), j);
                /*else if (strcmp(token, "help") == 0)
                    helppage(j);*/
                else if (strcmp(token, "mkdir") == 0)
                    create_dir(j, (*commands));
                else if (strcmp(token, "rmdir") == 0)
                    remove_dir(j, (*commands));
                else if (strcmp(token, "tictactoe") == 0)
                    play(j);
                else if (strcmp(token, "mv") == 0)
                    mv(j, (*commands));
                else if (strcmp(token, "calc") == 0)
                    calc(j);
                else
                {
                    dup2(saved_stdout, 1);
                    printf("No such Command.\n");
                }
            }
            return;
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            fd_in = fd[0];
            commands++;
            p++;
        }
    }
}
