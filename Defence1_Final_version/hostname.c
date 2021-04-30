#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include "hostname.h"


void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

// Driver code
void get_host_name(int nb_par, char** attributes)
{
    int I = 0;
    int a = 0;
    for(int i = 1; i < nb_par; i++)
    {
      if(strcmp(attributes[i],"-I") == 0)
      {
        I = 1;
      }
      if(strcmp(attributes[i],"-a") == 0)
      {
        a = 1;
      }
    }
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);

    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);

    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
    if(a)
    {
      printf("Hostname: %s\n", hostbuffer);
      printf("Host IP: %s\n", IPbuffer);
    }
    else if(I)
    {
      printf("Host IP: %s\n", IPbuffer);
    }
    else
    {
      printf("Hostname: %s\n", hostbuffer);
    }

    return;
}
