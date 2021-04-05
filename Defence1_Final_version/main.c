#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <err.h>
#include "functions.h"
#include "rm.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "tree.h"
// THE CORE OF THE SHELL
///colors
//colors
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
  printf(" %s$ ", res);
  reset();
}

void read_command(char **parameters, int *nb_par)
{
  char line[150];
	int sub_index = 0;
  int c = 0;
  int counter = 0;
  int i = 0;
  while (1)
 	{
 	  c = fgetc(stdin);
    line[counter] = (char) c;
    if (c == 10 && counter == 0)
    {
      *nb_par = 0;
      return;
    }
    if (c == 10)
      break;
    counter += 1;
  }

	line[counter] = 0;

	for (int j = 0; j <= counter; j++)
  {
    if (line[j] == ' ' && sub_index != 0)
    {
      parameters[i][sub_index] = 0;
			i++;
			sub_index = 0;
		}
    else if (line[j] == 0 && sub_index != 0)
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
      tree(*nb_par, parameters);
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
  char color[20];

  while (1)
  {
    char** parameters = malloc(500 * sizeof(char*));
    for (size_t i = 0; i < 500; i++)
      parameters[i] = calloc(100, sizeof(char));
    prompt(color);
    read_command(parameters, &nb_par);
    if (nb_par == 0)
    {
      free(parameters);
      continue;
    }
    if (fork() != 0)
    {
      wait(NULL);
      exit(1);
    }
    else
    {
      if (strcmp(parameters[0], "exit") == 0)
        exit(1);
      exec(color, parameters, &nb_par);
    }
    if (strcmp(parameters[0], "exit") == 0)
      exit(1);
    free(parameters);
  }
}
