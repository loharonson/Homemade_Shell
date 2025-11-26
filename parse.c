#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "parse.h"

#define BUFFER_SIZE 128

int parse_cmds(char * line, char*** cmd_ary){
  char * curr = line;
  char * token;
  int cmds = 1;
  char * prev = malloc(BUFFER_SIZE);
  char * cmd_buffer = malloc(BUFFER_SIZE);
  int i = 0;
  if(strchr(line, ';')){
    cmd_ary[i] = malloc(BUFFER_SIZE);
    strncpy(cmd_buffer, token - curr, token - curr);
    parse_args(cmd_buffer, cmd_ary[i]);
    return cmds;
  }
  while(token = strsep(&curr, ";")){
    cmd_ary[i] = malloc(BUFFER_SIZE);
    if(prev){

      strncpy(cmd_buffer, (int)(token - curr + prev), (int)(token - prev));
    }
    else{
      strncpy(cmd_buffer, (int)(token - curr), (int)(token - curr));
    }
    parse_args(cmd_buffer, cmd_ary[i]);
    prev = token;
    cmds++;
    i++;
  }
  return cmds;
}

void parse_args( char * line, char ** arg_ary ){
  char * curr = line;
  char * token;
  int i = 0;
  while((token = strsep(&curr, " "))){
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}
