#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char* pwd(int nb_par);
void create_dir(int nb_par, char** dirname);
void touch(char** filename, int nb_par);
void helppage(int nb_par);
void red();
void mv (char *file_1, char* file_2);
void remove_dir(int nb_par, char** dirname);
void echo(int nb_par, char** par);

#endif
