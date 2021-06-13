#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"

void alias(int nb_par, char** parameters, const char** commands)
{
    if (nb_par != 4)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: alias . Try 'help alias' for more information.awdawdawd\n");
      return;
    }
    if((strcmp(parameters[2], "=")) != 0)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: alias [alias] = [existing_command] . Try 'help' for more information %s.\n", parameters[2]);
      return;
    }


    if(strcmp(parameters[3], "pwd") == 0)
    {
      commands[0] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "help") == 0)
    {
      commands[1] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "mkdir") == 0)
    {
      commands[2] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "touch") == 0)
    {
      commands[3] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "mv") == 0)
    {
      commands[4] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "rmdir") == 0)
    {
      commands[5] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "color") == 0)
    {
      commands[6] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "clear") == 0)
    {
      commands[7] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "tree") == 0)
    {
      commands[8] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "rm") == 0)
    {
      commands[9] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "cat") == 0)
    {
      commands[10] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "ls") == 0)
    {
      commands[11] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "cd") == 0)
    {
      commands[12] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "echo") == 0)
    {
      commands[13] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "bg") == 0)
    {
      commands[14] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "sleep") == 0)
    {
      commands[15] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "job") == 0)
    {
      commands[16] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "grep") == 0)
    {
      commands[17] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "calc") == 0)
    {
      commands[18] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "hostname") == 0)
    {
      commands[19] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "alias") == 0)
    {
      commands[20] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "exit") == 0)
    {
      commands[21] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "setenv") == 0)
    {
      commands[22] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "unsetenv") == 0)
    {
      commands[23] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else if(strcmp(parameters[3], "tictactoe") == 0)
    {
      commands[24] = strdup(parameters[1]);
      printf("Succesfully set an alias for %s : %s\n", parameters[3], parameters[1]);
      return;
    }
    else
    {
      printf("Such a command does not exist\n");
      return;
    }
    return;
}
