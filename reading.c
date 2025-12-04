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

/* char* readingline()
  The arguments are nothing. Return value: string (char*).
  This function is meant to read through stdin in order to get the commands from the prompt.
*/

char* readingline(){
  char *buffer = malloc(200);
  buffer = fgets(buffer, 200, stdin);
  if(buffer == NULL){
    printf("\nGoodbye!\n");
    exit(0);
  }
  //strip newline if necessary
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}
