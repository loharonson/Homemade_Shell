#include <string.h>
#include <unistd.h>

void parse_args( char * line, char ** arg_ary ){
  //figure out how many commands are happening
  int j = 1;
  char * curr = line;
  char * token;
  while((token = strsep(&curr, ";"))){
    j++;
  }
  int i = 0;
  for(int h = 0; h < j; h++){
    while((token = strsep(&curr, " "))){
      if(strstr(token, ";")){
        //NEEDS TO BE DONE
      }
      arg_ary[i] = token;
      i++;
    }
    arg_ary[i] = NULL;
  }
}
