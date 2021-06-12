#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "functions.h"
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>


void set_env(char** parameters, int nb_par)
{
	if (nb_par == 3)
		setenv(parameters[1], parameters[2], 1);
	else if (nb_par == 2)
		setenv(parameters[1], " ", 1);
	else{
		printf("Invalid arguments: Use help to know more\n");
		return;
	}
	return;
}

void unset_env(char** parameters, int nb_par)
{
	if (nb_par != 2)
	{
		printf("Only 1 argument expected\n");
		return;
	}
	unsetenv(parameters[1]);
	return;
}