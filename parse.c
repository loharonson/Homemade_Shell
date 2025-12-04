#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "parse.h"

#define BUFFER_SIZE 128

int parse_args( char * line, char ** arg_ary, char * delimiter){
  char * curr = line;
  char * token;
  int i = 0;
  while((token = strsep(&curr, delimiter))){
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return i;
}
