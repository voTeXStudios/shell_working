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
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include "job_struct.h"

void bg(char* job_nb, int k, int back_count, job back[])
{
    int proc = atoi(job_nb);
    if (k >= 3)
        printf("Too many arguments\n");
    else if (k <= 1)
        printf("Too few arguments\n");
    else
    {
        if (proc > back_count)
            printf("No such job\n");
        else
        {
            pid_t pid = back[proc].pid;
            kill(pid, SIGTTIN);
            kill(pid, SIGCONT);
        }
    }
}
