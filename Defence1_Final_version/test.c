#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *line = readline("");
    printf("%s\n", line);
    return 0;
}
