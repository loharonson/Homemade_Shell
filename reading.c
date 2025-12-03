#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include "main.h"
/*
int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
*/

/* readingline()
  The arguments are nothing. Return value: string (char*).
  This function is meant to read through stdin in order to get the commands from the prompt.
*/

char* readingline(){
  char * returnable;
  char buffer[200];
  fgets(buffer, 200, stdin)
  strcpy(returnable, buffer);
  return returnable;
}
