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
      before_args[i] = NULL;
      strcpy(destination, args[i + 1]);
      break;
    }
    before_args[i] = args[i];
    i++;
  }
  //if there's nothing after the redirect just execvp
  if(i == len - 1){
    int stdout = STDOUT_FILENO;
    int backup_stdout = dup(stdout);
    if(is_append){
      int file = open(destinaion, O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else{
      int file = open(destinaion, O_WRONLY | O_CREAT, 0644);
    }
    if(file == -1){
      printf("%s\n", strerror(errno));
    }
    dup2(file, stdout);
    int p = fork();
    if(p == -1){
      printf("%s\n", strerror(errno));
    }
    if(p == 0){
      execvp(before_args[0], before_args);
    }
    int status;
    pid_t exit_child = wait(&status);
    if(exit_child == -1){
      printf("%s\n", strerror(errno));
    }
    if(WIFEXITED(status)){
      //reset stdout just in case
      fllush(stdout);
      dup2(backup_stdout, stdout);
      exit(0);
    }
  }

}

/*redirect_stdin()
  Arguments: None. Return: None.
  This function redirects stdin from a file, titled "lines.txt"*/
void redirect_stdin(){
  int x = open("lines.txt", O_RDONLY);
  if(x <0){
    err();
  }
  int stdin = STDIN_FILENO;
  dup2(x, stdin);
  close(x);
  printf("Testing the redirect_in DELETE WHEN WORKING");
}

/*currents()
  Arguments: None. Return: char*(string)
  This function uses the getcwd() command and puts it to a buffered string called currentdir.
  The returned char* string is called currentdir.*/

char* currents(){
  char currentdir[100];
  getcwd(currentdir, sizeof(currentdir));
  printf("Current Directory: %s\n", currentdir);
  char *str = (char*) malloc(101);
  if(str == NULL){
    return NULL;
  }
  strcpy(str, currentdir);
  return str;
}

/* char* changing_dirs(char * desires)
  Arguments: char * desires -- this is the char* that is the desired directory we want to move to. like "cd ____"
  Output: string that shows the current directory
  Working: uses chdir to change the directory to the desired directory, checks for errors, and then uses
  currents() in order to print the current directoryy*/
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
