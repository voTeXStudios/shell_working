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
    fprintf(stderr, "SYNTAX ERROR:\nUsage: pwd. Try 'help' for more information.\n");
    return NULL;
  }
  char buff[FILENAME_MAX];
  char* current_working_dir = getcwd(buff, FILENAME_MAX);
  if (current_working_dir == NULL)
  {
    fprintf(stderr, "Error trying to get file\n");
    return NULL;
  }
  return current_working_dir;
}

void create_dir(int nb_par, char** dirname) //this is the mkdir fn, handles errors
{
  if(nb_par == 1)
    fprintf(stderr, "SYNTAX ERROR:\nUsage: mkdir [dir_name]. Try 'help' for more information.\n");
  
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
    fprintf(stderr, "SYNTAX ERROR:\nUsage: touch [file_name]. Try 'help' for more information.\n");
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

void helppage(int nb_par)
{
  if(nb_par > 1)
  {
    fprintf(stderr, "SYNTAX ERROR:\nUsage: help. Try 'help' for more information.\n");
    return;
  }
  printf(
         "Hello and welcome to our shell!!\n\n"
         "Here is an example of how the help page works : commandName_flags_arguments means that '_' must be replaced with a space and the rest is pretty self-explanatory \n\n"
         "Here is a list of our commands and what they do:\n\n"
         "cat_attributes_arg(s) - Prints out contents of the file(s) arg(s)\n\n"
         "   - attributes: '-E' - used to display $ at end of each line\n\n"
         "                 '-n' - used to number all output lines\n\n"
         "cd_arg                - Changes current working directory into arg\n\n"
         "color_arg             - Changes the color of the prompt to 'arg'\n\n"
         "echo_str              - Prints out 'str' in the STDOUT\n\n"
         "help                  - Prints out this manual\n\n"
         "ls_attributes         - Lists out the files directories in your current working directory\n\n"
         "   - attributes: '-a' - used to not ignore entries starting with '.'\n\n"
         "mkdir_arg(s)          - Creates a directory or multiple directories with DirName = arg(s)\n\n"
         "mv_arg1_arg2          - Rename arg1(file) to arg2(file) or moves arg1(file) to arg2(directory)\n\n"
         "pwd                   - Prints out your current working directory\n\n"
         "rm_arg(s)             - Removes the file(s) with FileName = arg(s)\n\n"
         "rmdir_attributes_arg1 - Removes the directory or multiple directories with DirName = arg(s)\n\n"
         "   - attributes: '-f' - used to delete non-empty directories\n\n"
         "touch_arg(s)          - Creates file(s) with FileName = arg(s)\n\n"
         "tree_arg              - Prints the directories/sub-directories and files in tree structure\n\n"  
         "clear                 - Clears the terminal. Similar to what we have in bash\n\n"           
        );
}

void mv(char *file_1, char *file_2)
{
  if (rename(file_1, file_2) == -1 )
  {
    fprintf(stderr, "An error has occured during the process");
    return;
  }
}

void remove_dir(int nb_par, char** dirname) //this is the rmdir fn with "-f", handles errors
{
  if(nb_par == 1)
  {
    fprintf(stderr, "SYNTAX ERROR:\nUsage: rmdir [dir_name]. Try 'help' for more information.\n");
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

void echo(int nb_par, char** par)
{
    for(int i = 1; i < nb_par; i++)
      printf("%s ", par[i]);
    printf("\n");
}

void clear(int nb_par)
{
  if (nb_par > 1)
  {
    fprintf(stderr, "Too many arguments: Type '-help' to know more\n");
    return;
  }
  const char* screen_clear = " \e[1;1H\e[2J";
  if (write(STDOUT_FILENO, screen_clear, 12) == -1){
      fprintf(stderr, "Error while clearing the screen");
      return;
  }
}
