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

static int filter(){
    return 1;
}

void print_error_ls(char *this, char *dir){
    fprintf(stderr, "%s cannot list from %s\n%s\n", this, dir, strerror(errno));
}

void print_usage_ls(){
    puts("ERROR:");
    fprintf(stderr, "Invalid Operand: Type 'help' to know more\n");
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

void print_files_dir(int a_triggered, struct dirent **contents, int content_count)
{
    
    struct stat st;
    int stat_check;
    if (a_triggered == 0)
    {
        for(int i = 0; i<content_count; i++)
        {
            if (contents[i] -> d_name[0] == '.')
                continue;
            stat_check = stat(contents[i]->d_name, &st);
            if (stat_check == 0 && S_ISDIR(st.st_mode))
                blue1();
            else if (stat_check == 0 && st.st_mode & S_IXUSR)
                green1();
            
            puts(contents[i]->d_name);
            reset1();
        }
        return;
    }
    for(int i = 0; i<content_count; i++)
    {
        stat_check = stat(contents[i]->d_name, &st);
        if ((stat_check == 0 && S_ISDIR(st.st_mode)) || contents[i]->d_name[0] =='.')
            blue1();
        else if (stat_check == 0 && st.st_mode & S_IXUSR)
            green1();
        puts(contents[i]->d_name);
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
    int content_count;
    struct dirent **contents;
    if (*file_dir_exists == 0)
    {
        if ((content_count = scandir("./", &contents, filter, alphasort)) < 0)
        {
            print_error_ls(argv[0], "./");
            return;
        }
        printf("./:\n");
        print_files_dir(*a_triggered, contents, content_count);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 && strcmp(argv[i], "-A") != 0)
            {
                if ((content_count = scandir(argv[i], &contents, filter, alphasort)) < 0){
                    print_error_ls(argv[0], argv[i]);
                    return;
                }
                printf("%s:\n", argv[i]);
                print_files_dir(*a_triggered, contents, content_count);
                if (i != argc - 1)
                    printf("\n");
            }
        }

    }

}

int _ls(int argc, char *argv[]){
    int a_triggered = 0;
    int file_dir_exists = 0;
    int content_count;
    struct dirent **contents;

    if (argc == 1)
    {
        if ((content_count = scandir("./", &contents, filter, alphasort)) < 0)
        {
            print_error_ls(argv[0], "./");
            return 1;
        }
        printf("./:\n");
        print_files_dir(a_triggered, contents, content_count);
        return 0;
    }
    check_arguments(argc, argv, &a_triggered, &file_dir_exists);
    _list(argc, argv, &a_triggered, &file_dir_exists);
    return 0;
}

