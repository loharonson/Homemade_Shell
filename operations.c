#include <unistd.h>
#include <sys/wait.h>
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

void redirect_stdout_overwrite(char ** args){
  char * before_after[3] = redirect_general(args);
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
}

void redirect_stdout_append(char ** args){
  char * before_after[3] = redirect_general(args);
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
