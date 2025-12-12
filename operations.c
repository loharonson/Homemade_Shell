#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "operations.h"

#define BUFFER_SIZE 128

//takes an args array, int to serve as a boolean for if >> or >, int len for when looping through
//finds the redirector, runs execvp itself
//void, returns nothing
void redirect_stdout(char ** args, int is_append, int len){
  char * before_args[len];
  int i = 0;
  char * destination = malloc(BUFFER_SIZE);
  int stdout = STDOUT_FILENO;
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
  int file;
  if(is_append){
    file = open(destination, O_WRONLY | O_CREAT | O_APPEND, 0644);
  }
  else{
    file = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  }
  if(file == -1){
    printf("%s\n", strerror(errno));
    exit(1);
  }
  dup2(file, stdout);
  execvp(before_args[0], before_args);
}

/*redirect_stdin()
  Arguments: char ** name-- the name of the file we are reading from and int len, the length of the arg array. Return: None.
  This function redirects stdin from a file, titled "lines.txt"
  */
void redirect_stdin(char ** args, int len){
  char * after_redirect[len];
  char * source = malloc(BUFFER_SIZE);
  int i = -1;
  int out = 0;
  for(int j = 0; j < len; j++){
    if(!strcmp(args[j],"<")){
      i = j + 1;
      break;
    }
    else{
      after_redirect[out++] = args[j];
    }
  }
  strcpy(source, args[i]);
  int x = open(source, O_RDONLY);
  if(x <0){
    err();
  }
  dup2(x, STDIN_FILENO);
  close(x);
  //make the after_redirect, then do special stuff if necessary
  int specials = 0;
  int first_index;

  for(int j = i + 1; j < len && args[j]; j++){
    after_redirect[out] = args[j];
    if(!specials){
      if(!strcmp(args[j], "|")){
        specials = 1;
        first_index = out;
      }
      if(strchr(args[j], '>')){
        specials = 1;
        first_index = out;
      }
    }
    out++;
  }
  after_redirect[out] = NULL;
  if(specials){
    if(!strcmp(after_redirect[first_index], "|")){
      pipe_func(after_redirect);
    }
    else{
      if(strstr(after_redirect[first_index], ">>")){
        redirect_stdout(after_redirect, 1, out);
      }
      else{
        redirect_stdout(after_redirect, 0, out);
      }
    }
  }
  else{
    execvp(after_redirect[0], after_redirect);
    err();
  }
}

/*currents()
  Arguments: None. Return: char*(string)
  This function uses the getcwd() command and puts it to a buffered string called currentdir.
  The returned char* string is called currentdir.
*/

char* currents(){
  char currentdir[100];
  getcwd(currentdir, sizeof(currentdir));
  //printf("Current Directory: %s\n", currentdir);
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
  currents() in order to print the current directory
*/
char * changing_dirs(char * desires){
  if (!desires) {
    desires = "/";
  }
  if (chdir(desires) == -1) {
    printf("cd: %s: %s\n", desires, strerror(errno));
    return NULL;
  }
  ///int x = chdir(desires);
  /*
  if(x == -1){
    printf("%s\n", strerror(errno));
    return currents();
  }
  */
  //printf("Successfully changed the directory");
  //return currents();
  return NULL;
}

//takes args array, no return value, finds the pipe and then redirects
void pipe_func(char **args) {
    int i = 0;
    while (args[i] && strcmp(args[i], "|") != 0) i++;
    if (!args[i]) return;
    args[i] = NULL;
    char **left  = args;
    char **right = &args[i+1];
    pid_t p1 = fork();
    if (p1 == 0) {
        int tmp = open("midst.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (tmp < 0) err();
        dup2(tmp, STDOUT_FILENO);
        close(tmp);
        execvp(left[0], left);
        err();
    }
    waitpid(p1, NULL, 0);
    pid_t p2 = fork();
    if (p2 == 0) {
        int in = open("midst.txt", O_RDONLY);
        if (in < 0) err();
        dup2(in, STDIN_FILENO);
        close(in);
        execvp(right[0], right);
        err();
    }
    waitpid(p2, NULL, 0);
    remove("midst.txt");
}
