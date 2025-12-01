#include <unistd.h>

#define BUFFER_SIZE 128

char ** redirect_general(char ** args){
  char * out[2];
  out[0] = malloc(BUFFER_SIZE);
  int found_redirect = 0;
  int i = 0;
  while(!found_redirect){
    if(strchr(args[i], '>')){
      found_redirect = 1;
      out[1] = args[i + 1];
    }
    else{
      strcpy(out[0], args[i]);
      i++;
    }
  }
  return out;
}

void redirect_stdout_overwrite(char ** args){
  char * before_after[2] = redirect_general(args);

}
