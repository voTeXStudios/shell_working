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
#include"calc.h"
#include "grep.h"
#include "hostname.h"
#include "alias.h"
#include "echo.h"
#include "redirection.h"
#include "pipe.h"
#include "env.h"
#include "tic_tac_toe.h"
#include "invader.h"
#include "cmat.h"
#include "history.h"


job back[100];
int back_count = 0, shellid = 0, childpid = 0;
job fore;
const char** commands = NULL;

void prompt(char * color);
const char** default_commands = NULL;
/////////////////////////////////////////////////
void populateMenu(){
    static const char *items[] = {"pwd", "help", "mkdir", "touch", "mv", "rmdir",
                                  "color", "clear", "tree", "rm", "cat", "ls",
                                  "cd", "echo", "bg", "sleep", "job", "grep",
                                  "calc", "hostname", "alias", "exit", "setenv", "unsetenv",
                                  "tictactoe", "invader", "history"};


    static const char *def_items[] = {"pwd", "help", "mkdir", "touch", "mv", "rmdir",
                                  "color", "clear", "tree", "rm", "cat", "ls",
                                  "cd", "echo", "bg", "sleep", "job", "grep",
                                  "calc", "hostname", "alias", "exit", "setenv", "unsetenv",
                                  "tictactoe", "invader", "history"};


    commands = items;
    default_commands = def_items;
}
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


int check_redirection(char* token)
{
  int i;
  int l = strlen(token);

  for (i = 0; i < l; i++)
  {
    if (token[i] == '<' || (token[i] == '>' && token[i + 1] != '>'))
      return 2;
    if (token[i] == '>' && token[i + 1] == '>')
      return 3;
  }
  return 0;

}

int check_pipe(char* token)
{
  int i;
  int l = strlen(token);
  for (i = 0; i < l; i++)
  {
    if (token[i] == '|')
      return 1;
  }
  return 0;

}
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
  //printf("\033[0;31m");
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
  printf("<Vol-Tex-Sh:>~ ");
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

  char* path = pwd(1);
  printf("%s", path);
  reset();
}

char* read_command(char **parameters, int *nb_par)
{
  char *line;
  char* token;
  char* temp = malloc(200 * sizeof(char));
  int i = 0;
  line = readline("$~ ");
  strcpy(temp, line);
  token = strtok(line, " \n\t\r");

  while (token != NULL)
  {
    strcpy(parameters[i++], token);
    token = strtok(NULL, " \n\t\r");
  }
  *nb_par = i;
  //free(buf);
  return temp;
}



int exec(char** parameters, int *nb_par)
{
    if (strcmp(parameters[0], commands[0]) == 0 || strcmp(parameters[0], default_commands[0]) == 0){
      char* path = pwd(*nb_par);
      printf("%s\n", path);
      return 0;
    }
    else if (strcmp(parameters[0], commands[1]) == 0 || strcmp(parameters[0], default_commands[1]) == 0){
      helppage(*nb_par, parameters, commands, default_commands);
      return 0;
    }
    else if (strcmp(parameters[0], commands[2]) == 0 || strcmp(parameters[0], default_commands[2]) == 0){
      create_dir(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[3]) == 0 || strcmp(parameters[0], default_commands[3]) == 0){
      touch(parameters, *nb_par);
      return 0;
    }
    else if (strcmp(parameters[0], commands[4]) == 0 || strcmp(parameters[0], default_commands[4]) == 0){
      mv(*nb_par, parameters);
      return 0;
    }
    else if(strcmp(parameters[0], commands[5]) == 0 || strcmp(parameters[0], default_commands[5]) == 0){
      remove_dir(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[7]) == 0 || strcmp(parameters[0], default_commands[7]) == 0){
      clear(*nb_par);
      return 0;
    }
    else if (strcmp(parameters[0], commands[8]) == 0 || strcmp(parameters[0], default_commands[8]) == 0){
      _tree(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[9]) == 0 || strcmp(parameters[0], default_commands[9]) == 0){
      _delete(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[10]) == 0 || strcmp(parameters[0], default_commands[10]) == 0){
      _cat(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[11]) == 0 || strcmp(parameters[0], default_commands[11]) == 0){
      _ls(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[13]) == 0 || strcmp(parameters[0], default_commands[13]) == 0){
      echo(parameters, *nb_par);
      return 0;
    }
    else if (strcmp(parameters[0], commands[15]) == 0 || strcmp(parameters[0], default_commands[15]) == 0){
      sleep_fun(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[16]) == 0 || strcmp(parameters[0], default_commands[16]) == 0){
      print_jobs(back_count, back);
      return 0;
    }
    else if (strcmp(parameters[0], commands[17]) == 0 || strcmp(parameters[0], default_commands[17]) == 0){
      grep(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[19]) == 0 || strcmp(parameters[0], default_commands[19]) == 0){
      get_host_name(*nb_par, parameters);
      return 0;
    }
    else if (strcmp(parameters[0], commands[26]) == 0 || strcmp(parameters[0], default_commands[26]) == 0){
      history(*nb_par);
      return 0;
    }
    return 1;

}








int main()
{
  //MAIN LOOP OF THE SHELL

  populateMenu();
  int nb_par = 0;
  int pid;
  char color[10];
  char** parameters;
  char* buf;
  int check_red;
  int c;
  shellid = getpid();
  signal(SIGCHLD, SIG_IGN);
  signal(SIGCHLD, child_sig);
  signal(SIGINT, ctrl_c);
  signal(SIGTSTP, ctrl_z);
  prompt(color);

 
  
  //change_color("cyan", color);
  int index = 0;

  while (1)
  {
   
    childpid = -1;
    parameters = malloc(500 * sizeof(char*));

    for (size_t i = 0; i < 500; i++)
      parameters[i] = calloc(100, sizeof(char));

    buf = read_command(parameters, &nb_par);
   
    my_add_history(index, buf);
    index++;
    //printf("%s\n", dirname);
    if (nb_par > 0)
    {
      
      c = check_pipe(buf);
      check_red = check_redirection(buf);
      
      if (c == 1)
      {
        execute_pipe(buf);
        free(buf);
      }

      else if (check_red == 2 || check_red == 3)
      {
        redirection(buf, check_red-2);
        free(buf);
      }
      


      /// All the functions which do not need forking.
      else if (strcmp(parameters[0], commands[12]) == 0 || strcmp(parameters[0], default_commands[12]) == 0)
        cd(nb_par, parameters);

      else if (strcmp(parameters[0], commands[21]) == 0 || strcmp(parameters[0], default_commands[21]) == 0)
      {
        //strcat(dirname, "/history");
        remove("/tmp/.history");
        exit(1);
      }

      else if (strcmp(parameters[0], commands[20]) == 0 || strcmp(parameters[0], default_commands[20]) == 0)
        alias(nb_par, parameters, commands);

      else if (strcmp(parameters[0], commands[18]) == 0 || strcmp(parameters[0], default_commands[18]) == 0)
        calc(atoi(parameters[1]));

      else if (strcmp(parameters[0], commands[6]) == 0 || strcmp(parameters[0], default_commands[6]) == 0)
        change_color(parameters[1], color);

      else if (strcmp(parameters[0], commands[22]) == 0 || strcmp(parameters[0], default_commands[22]) == 0)
     
         set_env(parameters, nb_par);
       
    

      else if (strcmp(parameters[0], commands[23]) == 0 || strcmp(parameters[0], default_commands[23]) == 0)
        
        unset_env(parameters, nb_par);
    

      else if (strcmp(parameters[0], commands[24]) == 0 || strcmp(parameters[0], default_commands[24]) == 0)
        play(nb_par);
      
      else if (strcmp(parameters[0], commands[25]) == 0 || strcmp(parameters[0], default_commands[25]) == 0)
      { 
        SpaceInvaders(nb_par);
      }
    
      /*else if (strcmp(parameters[0], commands[26]) == 0 || strcmp(parameters[0], default_commands[26]) == 0)
        cmat(nb_par);*/
       
      
      // Call the functions which need forking.
      else
      {
        pid = fork();

        if (pid < 0){
          printf("Error: Fork failed\n");
          return 1;
        }
      
        else if (pid == 0)
        {
          setpgid(0, 0);
          int check = exec(parameters, &nb_par);

          if (check != 0){
            printf("SHELL: Unknown command. Type help to know more\n");
            return 1;
          }
        }
        else
        {

          childpid = pid;
          
          char name[100];
          strcpy(name, parameters[0]);

          for (int i = 0; i < nb_par - 1; i++)
          {
            strcat(name, " ");
            strcat(name, parameters[i]);
          }

          fore.pid = pid;
          strcpy(fore.name, name);
          fore.is_back = 0;
          waitpid(-1, NULL, WUNTRACED);
          //wait(NULL)

        }
       
      }     
      
    }
    prompt(color);
    
    free(parameters);
    
  }
  return 0;
}
    
