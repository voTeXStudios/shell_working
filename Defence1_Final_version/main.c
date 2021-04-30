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
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "functions.h"
#include "rm.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "tree.h"
#include "job_struct.h"
//#include "bg.h"
#include "grep.h"

job back[100];
int back_count = 0, shellid = 0, childpid = 0;
job fore;
/////////////////////////////////////////////////
/*void bg(char* job_nb, int k, int back_count, job back[])
{
    int proc = atoi(job_nb);
    if (k >= 3)
        printf("Too many arguments\n");
    else if (k <= 1)
        printf("Too few arguments\n");
    else
    {
        if (proc > back_count)
            printf("No such job\n");
        else
        {
            pid_t pid = back[proc].pid;
            kill(pid, SIGTTIN);
            kill(pid, SIGCONT);
        }
    }
}*/

void print_jobs(int back_count, job back[])
{
    int i;
    int j = 1;
    for (i = 1; i <= back_count; i++)
    {
        if (back[i].is_back == 1)
        {
            char stat[1000];
            char status;
            int p;
            long unsigned mem;
            char str[10];
            sprintf(str, "%d", back[i].pid);

            strcpy(stat, "/proc/");
            strcat(stat, str);
            strcat(stat, "/stat");
            FILE *fd;
            if ((fd = fopen(stat, "r")) == NULL)
            {
                printf("[%d] %s %s [%d]\n", j, "Done", back[i].name, back[i].pid);
            }
            else
            {
                fscanf(fd, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
                fclose(fd);
                printf("[%d] ", j);
                if (status == 'T')
                    printf("%s ", "Stopped");
                else
                    printf("%s ", "Running");
                printf("%s [%d]\n", back[i].name, back[i].pid);
            }
            j++;
        }
    }
}
/////////////////////////
void child_sig()
{
    pid_t pid;
    int x;
    pid = waitpid(WAIT_ANY, &x, WNOHANG);
    int i;
    for (i = 1; i <= back_count; i++)
    {
        if (back[i].pid == pid)
        {
            int exit_status = WEXITSTATUS(x);
            if (exit_status == 0)
                printf("\n%s with pid %d exited normally\n", back[i].name, back[i].pid);
            else
                printf("\n%s with pid %d exited with exit status %d\n", back[i].name, back[i].pid, exit_status);
            fflush(stdout);
            break;
        }
    }
    signal(SIGCHLD, child_sig);
}

void ctrl_c()
{
    pid_t p = getpid();
    if (p != shellid)
        return;
    if (childpid != -1)
        kill(childpid, SIGINT);
    signal(SIGINT, ctrl_c);
}

void ctrl_z()
{
    pid_t p = getpid();
    if (p != shellid)
        return;

    if (childpid != -1)
    {
        kill(childpid, SIGTTIN);
        kill(childpid, SIGTSTP);
        back_count++;
        back[back_count].pid = childpid;
        back[back_count].is_back = 1;
        strcpy(back[back_count].name, fore.name);
    }
    signal(SIGTSTP, ctrl_z);
}


void red (){
  printf("\033[0;31m");
}
void yellow(){
  printf("\033[0;33m");
}

void blue(){
  printf("\033[0;34m");
}

void purple(){
  printf("\033[0;35m");
}

void cyan(){
  printf("\033[0;36m");
}

void green () {
  printf("\033[0;32m");
}

void change_color(char *c, char *color){
      strcpy(color, c);
  }
void reset () {
  printf("\033[0m");
}

void prompt(char *color)
{
  static int f_time = 1;
  if (f_time){
    const char* screen_clear = " \e[1;1H\e[2J";
    if (write(STDOUT_FILENO, screen_clear, 12) == -1){
      fprintf(stderr, "Error while clearing the screen");
      return;
    }
    f_time = 0;
  }
  
  yellow();
  printf("Vol-Tex-Sh:~");
  if (strcmp(color, "yellow") == 0){
    yellow();
  }
  else if (strcmp(color, "purple") == 0){
    purple();
  }
  else if (strcmp(color, "blue") == 0){
    blue();
  }
  else if (strcmp(color, "red") == 0){
    red();
  }
  else if (strcmp(color, "green") == 0){
    green();
  }
  else{
    cyan();
  }

  char* res = pwd(1);
  printf(" %s", res);
  reset();
}

void read_command(char **parameters, int *nb_par)
{
  char *line;
	int sub_index = 0;
  int i = 0;
  line = readline("$ ");
  int j  = 0;
	while(line[j] != '\0')
  {
    if (line[j] == ' ' && sub_index != 0)
    {
      parameters[i][sub_index] = 0;
			i++;
			sub_index = 0;
		}
    else if (line[j] != ' ')
    {
			parameters[i][sub_index] = line[j];
			sub_index++;
    }
    j++;
  }
  if (line[j] == 0 && sub_index != 0)
  {
    parameters[i][sub_index] = 0;
    i++;
    sub_index = 0;
  }
  *nb_par = i;
  return;
}

void exec(char color[], char** parameters, int *nb_par)
{
  if (*nb_par != 0)
  {
    if (strcmp(parameters[0], "pwd") == 0){
      char* res = pwd(*nb_par);
      printf("%s\n", res);
      return;
    }
    else if (strcmp(parameters[0], "help") == 0){
      helppage(*nb_par);
      return;
    }
    else if (strcmp(parameters[0], "mkdir") == 0){
      create_dir(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "touch") == 0){
      touch(parameters, *nb_par);
      return;
    }
    else if (strcmp(parameters[0], "mv") == 0){
      mv(parameters[1], parameters[2]);
      return;
    }
    else if(strcmp(parameters[0], "rmdir") == 0){
      remove_dir(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "color") == 0){
      change_color(parameters[1], color);
      return;
    }
    else if (strcmp(parameters[0], "clear") == 0){
      clear(*nb_par);
      return;
    }
    else if (strcmp(parameters[0], "tree") == 0){
      _tree(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "rm") == 0){
      _delete(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "cat") == 0){
      _cat(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "ls") == 0){
      _ls(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "cd") == 0){
      cd(*nb_par, parameters);
      return;
    }
    else if (strcmp(parameters[0], "echo") == 0){
      echo(*nb_par, parameters);
      return;
    }
    /*else if (strcmp(parameters[0], "bg") == 0){
      bg(parameters[1], *nb_par, back_count, back);
      return;
    }*/
    else if (strcmp(parameters[0], "sleep") == 0){
      sleep_fun(atoi(parameters[1]));
      return;
    }
    else if (strcmp(parameters[0], "job") == 0){
      print_jobs(back_count, back);
      return;
    }
    else if (strcmp(parameters[0], "grep") == 0){
      grep(*nb_par, parameters);
      return;
    }
    else {
      red();
      printf("SHELL : Unknown command. Type help to list all the possible commands\n");
      return;
    }
  }
}
int main()
{
  //MAIN LOOP OF THE SHELL
  int nb_par = 0;
  int pid;
  char color[20];
  shellid = getpid();
  signal(SIGCHLD, SIG_IGN);
  signal(SIGCHLD, child_sig);
  signal(SIGINT, ctrl_c);
  signal(SIGTSTP, ctrl_z);
  prompt(color);


  while (1)
  {
    childpid = -1;
    char** parameters = malloc(500 * sizeof(char*));
    for (size_t i = 0; i < 500; i++)
      parameters[i] = calloc(100, sizeof(char));
    //prompt(color);
    read_command(parameters, &nb_par);

    if (nb_par == 0){
      prompt(color);
      free(parameters);
      continue;
    }

    if (strcmp(parameters[0], "cd") == 0){
      exec(color, parameters, &nb_par);
      prompt(color);
      free(parameters);
      continue;
    }

    pid = fork();
    if (pid != 0)
    {
      if (strcmp(parameters[0], "exit") == 0)
        exit(1);
      prompt(color);
      childpid = pid;
      char name[100];
      strcpy(name, parameters[0]);
      for (int i = 1; i< nb_par - 1; i ++)
      {
        strcat(name, " ");
        strcat(name, parameters[i]);
      }

      fore.pid = pid;
      strcpy(fore.name, name);
      fore.is_back = 0;
      waitpid(-1, NULL, WUNTRACED);
    }
    
    else
    {
      setpgid(0, 0);
      if (strcmp(parameters[0], "exit") == 0)
        exit(1);
      exec(color, parameters, &nb_par);
    }

    if (strcmp(parameters[0], "exit") == 0)
      exit(1);
    free(parameters);
  }
}
