#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include "ls.h"
/* ls command implementation with argument -a
   TODO: implement recursive -R and -s for size
*/

void blue1();
void reset1();
void green1();



void print_error_ls(char *this, char *dir){
    fprintf(stderr, "%s cannot list from %s\n%s\n", this, dir, strerror(errno));
}

void blue1(){
  printf("\033[0;34m");
}

void reset1() {
  printf("\033[0m");
}

void green1() {
  printf("\033[0;32m");
}

void print_files_dir(int a_triggered, DIR* folder, char* root_dir)
{

    struct stat st;
    struct dirent *entry;
    int stat_check;
    if (a_triggered == 0)
    {
        while ((entry=readdir(folder)))
        {
            if (entry->d_name[0] == '.')
                continue;
            char new_str[100];
            strcpy(new_str, root_dir);
            strcat(new_str, "/");
            strcat(new_str, entry->d_name);
            stat_check = stat(new_str, &st);
            
            if (stat_check == 0 && S_ISDIR(st.st_mode))
                blue1();
            
            else if (stat_check == 0 && st.st_mode & S_IXUSR)
                green1();
            
            puts(entry->d_name);
            reset1();
        }
        return;
    }
    while ((entry=readdir(folder)))
    {
        if (entry->d_name[0] == '.')
            blue1();
        char new_str[100];
        strcpy(new_str, root_dir);
        strcat(new_str, "/");
        strcat(new_str, entry->d_name);
        stat_check = stat(new_str, &st);

        if (stat_check == 0 && S_ISDIR(st.st_mode))
            blue1();
        else if (stat_check == 0 && st.st_mode & S_IXUSR)
            green1();

        puts(entry->d_name);
        reset1();
    }
    return;
}

void check_arguments(int argc, char*argv[], int* a_triggered, int* file_dir_exists)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-A") == 0 || strcmp(argv[i], "--all") == 0)
            *a_triggered = 1;
        else
            *file_dir_exists = 1;
    }

}

void _list(int argc, char* argv[], int* a_triggered, int* file_dir_exists)
{
    DIR *folder;
    int counter = 0;
    int nb_dir_in_args = 0;

    if (argc == 1)
    {
        folder = opendir("./");
        if (folder == NULL)
        {
            print_error_ls(argv[0], "./");
            return;
        }
        printf("./:\n");
        print_files_dir(*a_triggered, folder, "./");
        return;
    }
    if (*file_dir_exists == 0)
    {
        folder = opendir(".");
        if (folder == NULL)
        {
            print_usage_ls(argv[0], "./");
            return;
        }
        printf("./:\n");
        print_files_dir(*a_triggered, folder, "./");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0 || strcmp(argv[i], "-A") == 0)
                continue;
            nb_dir_in_args += 1;
        }
        
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 && strcmp(argv[i], "-A") != 0)
            {
                folder = opendir(argv[i]); 
                if (folder == NULL)
                {
                    print_usage_ls(argv[0], argv[i]);
                    return;
                }          
                printf("%s:\n", argv[i]);
                print_files_dir(*a_triggered, folder, argv[i]);
                if (counter != nb_dir_in_args - 1)
                    printf("\n");
                counter += 1;
            }
        }

    }

}

int _ls(int argc, char *argv[]){
    int a_triggered = 0;
    int file_dir_exists = 0;

    check_arguments(argc, argv, &a_triggered, &file_dir_exists);
    _list(argc, argv, &a_triggered, &file_dir_exists);
    return 0;
}
