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

/* char* readingline()
  The arguments are nothing. Return value: string (char*).
  This function is meant to read through stdin in order to get the commands from the prompt.
*/

char* readingline(){
  char buffer[200];
  if(fgets(buffer, 200, stdin) == NULL){
    return NULL;
  }
  char * returnable = malloc(201);
  if(returnable == NULL){
    return nULL;
  }
  strcpy(returnable, buffer);
  return returnable;
}
