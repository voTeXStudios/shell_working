#ifndef LS_H
#define LS_H

void print_error_ls(char *this, char *dir);
void print_files_dir(int a_triggered, DIR* folder, char* root_dir);
void check_arguments(int argc, char*argv[], int* a_triggered, int* file_dir_exists);
void _list(int argc, char* argv[], int* a_triggered, int* file_dir_exists);
int _ls(int argc, char *argv[]);

#endif
