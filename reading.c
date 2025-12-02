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
#include "main.c"

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

char* readingline(){
  char * returnable;
  //int x = open(stdin, O_RDONLY);
  File *f = fopen(stdin);
  char buffer[200];
  while(fgets(buffer, 200, f) != NULL){
    returnable = buffer;
    returnable++;
  }
  return returnable;
}
