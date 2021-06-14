#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "history.h"

void my_add_history(int index, char* cmd)
{
    FILE* file = fopen("/tmp/.history","ab+");
    if (file == NULL){
        printf("ERROR: Opening the file\n");
        return;
    }

    char number[200];
    sprintf(number, "%d", index);
    fprintf(file, "[%s]:   ", number);
    fputs(cmd, file);
    fputs("\n", file);
    fclose(file);
    
}

int history(int nb_par){
    if (nb_par > 1){
        printf("ERROR: Too many arguments. Type 'help history' to know more.'\n");
        return 1;
    }
    
    FILE* file = fopen("/tmp/.history","rb+");
    if (file == NULL){
        printf("No command history");
        return -1;
    }
    //int n = 1;
    int c = getc(file);
    while (c != EOF){
        printf("%c",c);
        c = getc(file);
    }
    fclose(file);
    return 0;
}
