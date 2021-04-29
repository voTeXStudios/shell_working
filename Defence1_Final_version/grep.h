#ifndef GREP_H
#define GREP_H
#include <stdio.h>

int grep(int argc, char **argv);
void compile_pattern(const char *pat);
void process(const char *name, FILE *fp);
void usage(void);

#endif