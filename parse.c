#include <string.h>
#include <unistd.h>

int parse_args( char * line, char *** arg_ary ){
  //figure out how many commands are happening
  int j = 1;
  char * curr = line;
  char * token;
  while((token = strsep(&curr, ";"))){
    j++;
  }
  for(int h = 0; h < j; h++){
    for(int i = 0; token = strsep(&curr, " "); i++){
      while((token = strsep(&curr, " "))){
        arg_ary[h][i] = token;
      }
    }
    arg_ary[h][i] = NULL;
  }
  return j;
}
