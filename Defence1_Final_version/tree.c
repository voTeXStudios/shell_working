#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "tree.h"

void my_error()
{
	fprintf(stderr, "Too many Arguments: Type 'help' to know more");
	return;
}

void PrintDirentStruct(char direntName[], int level, int* nb_dir, int* nb_file)
{
	         //Define a directory stream pointer
    DIR *p_dir = NULL;
 
         //Define a directory structure pointer
    struct dirent *p_dirent = NULL;
 
         //Open the directory and return a directory stream pointer to the first directory item
    p_dir = opendir(direntName);
    if(p_dir == NULL)
    {
        my_error("opendir error");
        return;
    }
 
         //Read each directory item in a loop, when it returns NULL, the reading is complete
    while((p_dirent = readdir(p_dir)) != NULL)
    {
                 //Directory name before backup
        char *backupDirName = NULL;
 
        if(p_dirent->d_name[0] == '.')
       		continue;
        
 
        int i;
        for(i = 0; i < level; i++)
        {
            printf("|");
            printf("     ");
        }
        printf("|--- ");
        printf("%s\n", p_dirent->d_name);
 

                 //If the directory item is still a directory, enter the directory
        if(p_dirent->d_type == DT_DIR)
        {
			*nb_dir += 1;
                         //Current directory length
            int curDirentNameLen = strlen(direntName) + 1;
 
                         //Backup
            backupDirName = (char *)malloc(curDirentNameLen);
            memset(backupDirName, 0, curDirentNameLen);
            memcpy(backupDirName, direntName, curDirentNameLen);
 
 
            strcat(direntName, "/");
            strcat(direntName, p_dirent->d_name);
            PrintDirentStruct(direntName, level + 1, nb_dir, nb_file);
 
 
                         //Restore the previous directory name
            memcpy(direntName, backupDirName, curDirentNameLen);
            free(backupDirName);
            backupDirName = NULL;
        }
		else
			*nb_file += 1;
 
    }
 
    closedir(p_dir);
}


int tree(int argc, char* argv[])
{
	char direntName[256];
	memset(direntName, 0, sizeof(direntName));
	int nb_dir = 0;
	int nb_file = 0;
	if (argc == 1)
		direntName[0] = '.';
	else if (argc == 2)
		strcat(direntName, argv[1]);
	else
    {
		my_error("argument error");
        return 1;
    }

	printf("%s\n", direntName);
	PrintDirentStruct(direntName, 0, &nb_dir, &nb_file);
	printf("\n%i directories, %i files\n", nb_dir, nb_file);
	return 0;
}
