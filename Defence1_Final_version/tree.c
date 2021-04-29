#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "tree.h"
#include <sys/stat.h>
#include <errno.h>

void my_error()
{
	fprintf(stderr, "Too many Arguments: Type 'help' to know more");
	return;
}

void blue_tree(){
  printf("\033[0;34m");
}

void reset_tree() {
  printf("\033[0m");
}

void green_tree() {
  printf("\033[0;32m");
}

static int filter(){
    return 1;
}

void DisplayIndent(char** indent, int* nb)
{
    for (int i = 0; i < *nb; i++)
        printf("%s", indent[i]);
}
void PrintDirentStruct(char direntName[], char** indent, int* nb_dir, int* nb_file, int *a_triggered, int* nb)
{
    int content_count;
    struct dirent **contents;
    struct stat buf;
    int stat_check;
    char* path;
    char* backupDirName;
    int curDirentNameLen;

    content_count = scandir(direntName, &contents, filter, alphasort);

    for (int i = 0; i < content_count; i++)
    {
        reset_tree();
        

        if (strcmp(contents[i]->d_name, "..") == 0 || strcmp(contents[i]->d_name, ".") == 0)
            continue;
        
        if (*a_triggered != 1 && contents[i]->d_name[0] == '.')
            continue;


        if (i < content_count - 1)
            indent[*nb] = "|-- ";
        else
            indent[*nb] = "+-- ";

        *nb += 1;

        DisplayIndent(indent, nb);

        path = calloc(256, sizeof(char));
        strcpy(path, direntName);
        strcat(path, "/");
        strcat(path, contents[i]->d_name);
        stat_check = stat(path, &buf);

        if (stat_check == 0 && S_ISDIR(buf.st_mode))
            blue_tree();
        else if (stat_check == 0 && buf.st_mode & S_IXUSR)
            green_tree();
        else 
            reset_tree(); 
        printf("%s\n", contents[i]->d_name);
        free(path);


        
        if (contents[i]->d_type == DT_DIR)
        {
            *nb_dir += 1;

            indent[*nb - 1] = NULL;
            *nb -= 1;
            if (i < content_count - 1)
                indent[*nb] = "|    ";
            else
                indent[*nb] = "    ";
            *nb += 1;
            //Current directory length
            curDirentNameLen = strlen(direntName) + 1;
 
                         //Backup
            backupDirName = (char *)malloc(curDirentNameLen);
            memset(backupDirName, 0, curDirentNameLen);
            memcpy(backupDirName, direntName, curDirentNameLen);
 
 
            strcat(direntName, "/");
            strcat(direntName, contents[i]->d_name);
            PrintDirentStruct(direntName, indent, nb_dir, nb_file, a_triggered, nb);
 
 
                         //Restore the previous directory name
            memcpy(direntName, backupDirName, curDirentNameLen);
            free(backupDirName);
            backupDirName = NULL;
        }
        else
            *nb_file += 1;
        indent[*nb - 1] = NULL;
        *nb -= 1;
    }

}


void check_arguments_tree(int argc, char* argv[], int *a_triggered, int *file_dir_exists)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0)
            *a_triggered = 1;
        else
            *file_dir_exists = 1;
    }
    
}

int _tree(int argc, char* argv[])
{
    
    int nb_file = 0;
    int nb_dir = 0;
    int a_triggered = 0;
    int file_dir_exists = 0;
    int nb;
    char** indent;
    if (argc < 2)
    {
        nb = 0;
        char direntName[256];
        indent = malloc(500 * sizeof(char*));
	    memset(direntName, 0, sizeof(direntName));
        direntName[0] = '.';
        printf("%s\n", direntName);
        PrintDirentStruct(direntName, indent, &nb_dir, &nb_file, &a_triggered, &nb);
        free(indent);
    }
    else
    {
        check_arguments_tree(argc, argv, &a_triggered, &file_dir_exists);

        if (file_dir_exists == 0)
        {
            nb = 0;
            char direntName[256];
            indent = malloc(500 * sizeof(char*));
	        memset(direntName, 0, sizeof(direntName));
            direntName[0] = '.';
            printf("%s\n", direntName);
            PrintDirentStruct(direntName, indent, &nb_dir, &nb_file, &a_triggered, &nb);
            free(indent);
            return 0;
        }
       
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-a") == 0)
                continue;
            char direntName[256];
            nb = 0;
            indent = malloc(500 * sizeof(char*));
            memset(direntName, 0, sizeof(direntName));
            strcat(direntName, argv[i]);
            printf("%s\n", direntName);
            PrintDirentStruct(direntName, indent, &nb_dir, &nb_file, &a_triggered, &nb);
            free(indent);
        }
    }
    printf("\n%i directories, %i files\n", nb_dir, nb_file);
	return 0;
}