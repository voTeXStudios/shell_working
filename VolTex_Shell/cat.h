#ifndef CAT_H
#define CAT_H

void check_flags(int argc, char* argv[], int* e_triggered, int* n_triggered, int* file_exists);
void rewrite(int fd_in, int fd_out, char *buf, int count, int e_triggered, int* n, int n_triggered);
void re_read(int fd_out, int fd_in, int e_triggered, int* n, int n_triggered);
void _cat(int argc, char *argv[]);

#endif
