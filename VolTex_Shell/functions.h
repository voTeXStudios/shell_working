#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char* pwd(int nb_par);
void create_dir(int nb_par, char** dirname);
void touch(char** filename, int nb_par);
void helppage(int nb_par, char **fns, const char **commands, const char **default_commands);
void mv(int nb_par, char **files);
void remove_dir(int nb_par, char** dirname);
void clear(int nb_par);
void sleep_fun(int nb_par, char **parameters);

#endif
