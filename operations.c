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

void redirect_stdout(char ** args, int is_append, int len){
  char * before_args[len];
  int i = 0;
  char * destination = malloc(BUFFER_SIZE);
  //loop up to the redirector
  while(i < len){
    if(strchr(args[i], '>')){
      strcpy(destination, args[i + 1]);
      break;
    }
    before_args[i] = args[i];
    i++;
  if(i == len - 1){
    
    exit(0);
  }
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
  int x = open("lines.txt", O_RDONLY);
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
