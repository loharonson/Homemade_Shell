#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

char ** redirect_general(char ** args){
  char * out[3];
  out[0] = malloc(BUFFER_SIZE);
  int found_redirect = 0;
  int i = 0;
  while(!found_redirect){
    if(strchr(args[i], '>')){
      found_redirect = 1;
      out[1] = args[i + 1];
      out[2] = (char)i;
    }
    else{
      strcpy(out[0], args[i]);
      i++;
    }
  }
  return out;
}

char ** redirect_stdout_overwrite(char ** args, int len){
  char * before_after[3];
  before_after = redirect_general(args);
  int stdout = STDOUT_FILENO;
  int backup_stdout = dup(stdout);
  if(p == -1)err();
  int file = open(before_after[0], O_WRONLY | O_CREAT, 0644);
  if(file == -1)err();
  dup2(file, stdout);
  int p = fork();
  if(p == 0){
    char ** new_args = {before, after, NULL};
    execvp(new_args[0], new_args);
  }
  int status;
  pid_t exit_child = wait(&status);
  if(exit_child < 0)err();
  if(WIFEXITED(status)){
    //reset stdout just in case
    fflush(stdout);
    dup2(backup_stdout, stdout);
  }
  char ** new_args[len - ]
}

char ** redirect_stdout_append(char ** args){
  char * before_after[3];
  before_after = redirect_general(args);
  int stdout = STDOUT_FILENO;
  int backup_stdout = dup(stdout);
  if(p == -1)err();
  int file = open(before_after[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
  if(file == -1)err();
  dup2(file, stdout);
  int p = fork();
  if(p == 0){
    char ** new_args = {before, after, NULL};
    execvp(new_args[0], new_args);
  }
  int status;
  pid_t exit_child = wait(&status);
  if(exit_child < 0)err();
  if(WIFEXITED(status)){
    //reset stdout just in case
    fflush(stdout);
    dup2(backup_stdout, stdout);
  }

}

void redirect_stdin(){
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

char * changing_dirs(char * desires){
  currents();
  int x = chdir(desires);
  if(x == -1){
    printf("%s\n", strerror(errno));
  }
  printf("Successfully changed the directory");
  return currents();
}

void pipe_func(char **args){

}
