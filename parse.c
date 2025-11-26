#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int parse_cmds(char * line char*** cmd_ary){
  char * curr = line;
  char * token;
  int cmds = 1;
  char * prev;
  char * cmd_buffer = malloc(BUFFER_SIZE);
  int i = 0;
  while(token = strsep(&curr, ";")){
    cmd_ary[i] = malloc(BUFFER_SIZE);
    if(prev){
      strncpy(cmd_buffer, token - curr + prev, token - prev);
    }
    else{
      strncpy(cmd_buffer, token - curr, token - curr);
    }
    parse_args(cmd_buffer, cmd_ary[i]);
    prev = token;
    cmds++;
    i++;
  }
  if(i == 0){
    cmd_ary[i] = malloc(BUFFER_SIZE);
    strncpy(cmd_buffer, token - curr, token - curr);
    parse_args(cmd_buffer, cmd_ary[i]);
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
