#include <string.h>
#include <unistd.h>

void parse_cmds(char * line char*** cmd_ary){
  char * curr = line;
  char * token;
  int i = 0;
  while(token = strsep(&curr, ";")){
    
  }
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
