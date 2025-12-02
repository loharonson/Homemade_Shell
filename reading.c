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

char* readingline(){
  char * returnable;
  char buffer[200];
  int i = 0;
  while(fgets(buffer, 200, stdin)){
    strcpy(returnable, buffer);
    i++;
  }
  if(i == 0){
    return NULL;
  }
  return returnable;
}
