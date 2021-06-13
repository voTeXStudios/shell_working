#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Done and dusted*/



void print_error(char *this, char *filename)
{
    fprintf(stderr, "%s: could not delete file %s;\n%s\n",
            this, filename, strerror(errno));
    return;
}

void print_usage()
{
    fprintf(stderr, "Invalid Operand: Type 'help' to know more\n");
    printf("ERROR: Is a directory\n");
    return;
}
void print_no_arg_err()
{
    fprintf(stderr, "Invalid Operand: Type 'help' to know more\n");
    printf("ERROR: File path invalid\n");
    return;
}
int isDirExits(const char *path)
{
    struct stat buf;
    stat(path,&buf);

    if(S_ISDIR(buf.st_mode))
        //Directory exists
        return 0;
    else
        return 1;
}

void _delete(int argc, char **argv)
{
    for (int i = 1; i< argc; i++){
        if (isDirExits(argv[i]) == 1)
        {
            if(remove(argv[i]))
                print_error("rm", argv[i]);
        }
        else
            print_usage("rm");
    }
}
