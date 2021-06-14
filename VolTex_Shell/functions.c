#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "functions.h"
#include <dirent.h>




char* pwd(int nb_par) // shows the current working dir, no errors to handle
{
    if(nb_par > 1)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: pwd. Try 'help pwd' for more information.\n");
      return NULL;
    }
    char buff[FILENAME_MAX];
    char* current_working_dir = getcwd(buff, FILENAME_MAX);
    if (current_working_dir == NULL)
    {
      fprintf(stderr, "Error trying to get file\n");
      return NULL;
    }
    //printf("%s", current_working_dir);
    return current_working_dir;
}

void create_dir(int nb_par, char** dirname) //this is the mkdir fn, handles errors
{
    if(nb_par == 1)
      fprintf(stderr, "SYNTAX ERROR:\nUsage: mkdir [dir_name]. Try 'help mkdir' for more information.\n");

    for (int i = 1; i < nb_par; i++)
    {
      int check;
      check = mkdir(dirname[i],0777);
      if (check)
      {
        fprintf(stderr, "There was an error creating the folder, maybe it already exists\n");
        return;
      }
    }
}

void touch(char** filename, int nb_par) //creates files, handles errors
{
    if(nb_par == 1)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: touch [file_name]. Try 'help touch' for more information.\n");
      return;
    }
    for (int i = 1; i < nb_par; i++)
    {
      FILE *file = fopen(filename[i], "w+");
      if(file == NULL)
      {
        fprintf(stderr, "There was an error creating the file\n");
        return;
      }
      fclose(file);
    }
}

void helppage(int nb_par, char **fns, const char **commands1, const char **default_commands1)
{
    if(nb_par < 2)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: help [fn_name]. Try 'help help' for more information.\n");
      return;
    }
    if (strcmp(fns[1], commands1[0]) == 0 || strcmp(fns[1], default_commands1[0]) == 0)
    {
      printf(
             "\nUSAGE : pwd\n\n"
             "pwd - Prints out your current working directory.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[1]) == 0 || strcmp(fns[1], default_commands1[1]) == 0)
    {
      printf(
              "\nUSAGE : help [fn_name]\n\n"
              "help - Prints out the usage of the fn_name entered.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[2]) == 0 || strcmp(fns[1], default_commands1[2]) == 0)
    {
      printf(
              "\nUSAGE : mkdir [dir_name]s\n\n"
              "mkdir - Creates a directory or multiple directories with DirName = dir_name.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[3]) == 0 || strcmp(fns[1], default_commands1[3]) == 0)
    {
      printf(
              "\nUSAGE : touch [file_name]s\n\n"
              "touch - Creates file(s) with FileName = file_name.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[4]) == 0 || strcmp(fns[1], default_commands1[4]) == 0)
    {
      printf(
              "\nUSAGE : mv [file_name1] [file_name2/dir_name]\n\n"
              "mv - Rename [file_name1] to [file_name2] or moves [file_name1] to [dir_name].\n\n"
            );
    }
    else if(strcmp(fns[1], commands1[5]) == 0 || strcmp(fns[1], default_commands1[5]) == 0)
    {
      printf(
              "\nUSAGE : rmdir [attributes] [dir_name]\n\n"
              "rmdir - Removes the directory or multiple directories with DirName = arg(s).\n\n"
              "      - attributes: '-f' - used to delete non-empty directories.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[7]) == 0 || strcmp(fns[1], default_commands1[7]) == 0)
    {
      printf(
              "\nUSAGE : clear\n\n"
              "clear - Clears the terminal.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[8]) == 0 || strcmp(fns[1], default_commands1[8]) == 0)
    {
      printf(
              "\nUSAGE : tree\n\n"
              "tree - Prints the directories/sub-directories and files in tree structure.\n\n"
              "     - attributes: '-a' - used to include hidden files.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[9]) == 0 || strcmp(fns[1], default_commands1[9]) == 0)
    {
      printf(
              "\nUSAGE : rm [file_name]s\n\n"
              "rm - Removes the file(s) with FileName = file_name.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[10]) == 0 || strcmp(fns[1], default_commands1[10]) == 0)
    {
      printf(
              "\nUSAGE : cat [attributes] [file_name]s\n\n"
              "cat - Prints out contents of the file(s) with FileName = file_name.\n\n"
              "    - attributes: '-n' -Prints the line number.\n\n"
              "                  '-E' -Prints $ before each line.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[11]) == 0 || strcmp(fns[1], default_commands1[11]) == 0)
    {
      printf(
              "\nUSAGE : ls [attributes] [file_name]s\n\n"
              "ls - Lists out the files directories in your current working directory.\n\n"
              "   - attributes: '-a' - used to include hidden files.\n\n"
              "                 '-l' - used to print stats of the files\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[13]) == 0 || strcmp(fns[1], default_commands1[13]) == 0)
    {
      printf(
              "\nUSAGE : echo [attributes] [file_name]s\n\n"
              "echo -  Prints out 'str' in a file discriptor.\n\n"
            ); //change this for later
    }
    else if (strcmp(fns[1], commands1[15]) == 0 || strcmp(fns[1], default_commands1[15]) == 0)
    {
      printf(
              "\nUSAGE : sleep [number]\n\n"
              "sleep -  Pauses for [number] seconds.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[16]) == 0 || strcmp(fns[1], default_commands1[16]) == 0)
    {
      printf(
              "\nUSAGE : job\n\n"
              "job -  Prints all the background processes.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[17]) == 0 || strcmp(fns[1], default_commands1[17]) == 0)
    {
      printf(
              "\nUSAGE : grep [attributes] [pattern] [file_name]s\n\n"
              "grep - Used to find certain patterns from given file(s) with FileName = file_name.\n\n"
              "     - attributes: -E    - Extended regular expression\n\n"
              "                   -i    - Ignore case\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[19]) == 0 || strcmp(fns[1], default_commands1[19]) == 0)
    {
      printf(
              "\nUSAGE : hostname [attributes]\n\n"
              "hostname - Prints hostname and/or IP address of current host.\n\n"
              "         - attributes: -I    - Prints out the IP address of current host\n\n"
              "                       -a    - Prints out all the information available to this function\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[12]) == 0 || strcmp(fns[1], default_commands1[12]) == 0)
    {
      printf(
              "\nUSAGE : cd [dir_name]\n\n"
              "cd -  Changes current working directory into [dir_name].\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[21]) == 0 || strcmp(fns[1], default_commands1[21]) == 0)
    {
      printf(
              "\nUSAGE : exit\n\n"
              "exit -  Quits the terminal.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[20]) == 0 || strcmp(fns[1], default_commands1[20]) == 0)
    {
      printf(
              "\nUSAGE : alias [alias] = [existing_command]\n\n"
              "alias -  Used to create aliases for already existing commands1.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[18]) == 0 || strcmp(fns[1], default_commands1[18]) == 0)
    {
      printf(
              "\nUSAGE : calc\n\n"
              "calc -  Opens a scientific calculator in the terminal.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[6]) == 0 || strcmp(fns[1], default_commands1[6]) == 0)
    {
      printf(
              "\nUSAGE : color [color_name]\n\n"
              "color -  Used to change the color of the prompt to [color_name].\n\n"
            );
    }

    else if (strcmp(fns[1], commands1[22]) == 0 || strcmp(fns[1], default_commands1[22]) == 0)
    {
      printf(
              "\nUSAGE : setenv [VAR] [val]\n\n"
              "setenv -  Sets the value of an environment variable.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[23]) == 0 || strcmp(fns[1], default_commands1[23]) == 0)
      {
        printf(
                "\nUSAGE : unsetenv [VAR]\n\n"
                "unsetenv -  Unsets the value of the environment variable.\n\n"
              );
      }
    else if (strcmp(fns[1], commands1[24]) == 0 || strcmp(fns[1], default_commands1[24]) == 0){
      printf(
              "\nUSAGE : tictactoe\n\n"
              "tictactoe - Launches a game of TicTacToe.\n\n"
            );
    }
    else if (strcmp(fns[1], commands1[25]) == 0 || strcmp(fns[1], default_commands1[25]) == 0)
    {
      printf(
        "\nUSAGE: invader\n\n"
        "invader - Launches a space invader game on shell.\n\n"
      );
    }
    else if (strcmp(fns[1], commands1[26]) == 0 || strcmp(fns[1], default_commands1[26]) == 0)
    {
      printf(
        "\nUSAGE: history\n\n"
        "history - prints the history of the commands used since the start of the shell session.\n\n"
      );
    }
    else if (strcmp(fns[1], commands1[27]) == 0 || strcmp(fns[1], default_commands1[27]) == 0)
    {
      printf(
        "\nUSAGE: chmod [MODE in Integer] file\n\n"
        "chmod - Changes the permissions of a file\n\n"
      );
    }
    else
      printf("%s : command not found\n", fns[1]);

    return;
}

void mv(int nb_par, char **files)
{
    if(nb_par < 3)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUSAGE : mv [file_name] [file_name/dir_name]. Try 'help mv' for more information.\n");
      return;
    }
    if (rename(files[1], files[2]) == -1)
    {
      fprintf(stderr, "An error has occured during the process");
      return;
    }
}

void remove_dir(int nb_par, char** dirname) //this is the rmdir fn with "-f", handles errors
{
  if(nb_par == 1)
  {
    fprintf(stderr, "SYNTAX ERROR:\nUsage: rmdir [dir_name]. Try 'help rmdir' for more information.\n");
    return;
  }
  int f = 0;
  for(int i = 1; i < nb_par; i++)
  {
    if(strcmp(dirname[i],"-f") == 0)
    {
      f = 1;
      break;
    }
  }
  for (int i = 1; i < nb_par; i++)
  {
    if(f)
    {
      if(strcmp(dirname[i],"-f") == 0)
        continue;
      DIR *theFolder = opendir(dirname[i]);
      if (theFolder == NULL)
      {
        fprintf(stderr, "No such directory : %s", dirname[i]);
        return;
      }
      struct dirent *next_file;
      char filepath[FILENAME_MAX];

      while ((next_file = readdir(theFolder)) != NULL)
      {
        sprintf(filepath, "%s/%s", dirname[i], next_file->d_name);
        remove(filepath);
      }
      closedir(theFolder);
      rmdir(dirname[i]);
    }
    else
    {
      DIR *theFolder = opendir(dirname[i]);
      if (theFolder == NULL){
        fprintf(stderr, "No such directory : %s", dirname[i]);
        return;
      }
      closedir(theFolder);
      int check;
      check = rmdir(dirname[i]);
      if (check)
      {
        fprintf(stderr, "This dirrectory is not empty : %s (try using the -f flag)\n", dirname[i]);
        return;
      }
    }
  }
}



void clear(int nb_par)
{
  if (nb_par > 1)
  {
    fprintf(stderr, "SYNTAX ERROR:\nUSAGE : clear. Type 'help clear' to know more\n");
    return;
  }
  const char* screen_clear = " \e[1;1H\e[2J";
  if (write(STDOUT_FILENO, screen_clear, 12) == -1){
      fprintf(stderr, "Error while clearing the screen");
      return;
  }
}

void sleep_fun(int nb_par, char** fns)
{
  if(nb_par != 2)
  {
    fprintf(stderr, "SYNTAX ERROR:\nUSAGE : sleep [number]. Try 'help sleep' for more information.\n");
    return;
  }
  sleep(atoi(fns[1]));
}
