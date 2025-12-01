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

void redirect_in(){
  int x = open("inputs.txt", O_RDONLY);
  int stdin = STDIN_FILENO;
  int backup_inputs = dup(x);
  dup2(stdin, x);
  printf("Testing the redirect_in DELETE WHEN WORKING");
}

char* currents(){
  char currentdir[100];
  getcwd(&currentdir, sizeof(currentdir));
  printf("Current Directory: %s\n", currentdir);
  char *str = (char*) malloc(sizeof(currentdir));
  if(str == NULL){
    return NULL;
  }
  strcpy(str, currentdir);
  return str;
}

void changing_dirs(char * desires){
  currents();
  int x = chdir(desires);
  if(x == -1){
    err();
  }
  printf("Successfully changed the directory");
  currents();
}
