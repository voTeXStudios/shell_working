#ifndef LS_H
#define LS_H

void printall(char* file, char* c);
void print_error_ls(char *this, char *dir);
void print_files_dir(int a_triggered, int l_triggered, DIR* folder, char* root_dir);
void check_arguments(int argc, char*argv[], int* a_triggered, int* l_triggered, int* file_dir_exists);
void _list(int argc, char* argv[], int* a_triggered, int* l_triggered, int* file_dir_exists);
void _ls(int argc, char *argv[]);

#endif
