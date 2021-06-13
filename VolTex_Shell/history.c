#include <stdlib.hnt>
#include <stdio.h>
#include "history.h"

void my_add_history(char * cmd, FILE *file){

    file = fopen(".history","wb");
    fprintf(file,"%s\n",cmd);
    fclose(file);
    return 0;
}

int history(void){
    FILE *file;
    file = fopen(".history","r");
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
