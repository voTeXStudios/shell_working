#ifndef _CHMOD_H_
#define _CHMOD_H_

#include <sys/types.h>
#include <sys/stat.h>

int Chmod(const char* path, mode_t mode);

#endif