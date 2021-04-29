#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "cd.h"

void print_error_cd(char *this, char *dirname)
{
    fprintf(stderr, "%s cannot go to %s\n%s\n", this, dirname, strerror(errno));
    return;
}
void print_usage_cd()
{
    fprintf(stderr, "Too many arguments: Type 'help' to know more\n");
    return;
}
int cd(int argc, char *argv[])
{
    errno = 0;
    struct passwd *user;
    int check;
    if (argc == 2)
    {
        check = chdir(argv[1]);
        if (check != 0)
            print_error_cd(argv[0], argv[1]);
    }
    else if (argc == 1)
    {
        user = getpwnam(getlogin());
        check = chdir(user->pw_dir);
        printf("to home\n");
        if (check != 0)
            print_error_cd(argv[0], argv[1]);
    }
    else
        print_usage_cd();
    return 0;
}
