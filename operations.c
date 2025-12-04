#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 128

//err function, no args, exits, makes errors readable
int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

//takes an args array, int to serve as a boolean for if >> or >, int len for when looping through
//finds the redirector, runs execvp itself
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
    int stdout = STDOUT_FILENO;
    int backup_stdout = dup(stdout);
    int file;
    if(is_append){
      file = open(destination, O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else{
      file = open(destination, O_WRONLY | O_CREAT, 0644);
    }
    if(file == -1){
      printf("%s\n", strerror(errno));
    }
    dup2(file, stdout);
    execvp(before_args[0], before_args);
}

/*redirect_stdin()
  Arguments: char ** name-- the name of the file we are reading from. Return: None.
  This function redirects stdin from a file, titled "lines.txt"
  */
void redirect_stdin(char ** name){
  int x = open(*name, O_RDONLY);
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
  The returned char* string is called currentdir.
*/

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
  currents() in order to print the current directory
*/
char * changing_dirs(char ** desires){
  currents();
  int x = chdir(*desires);
  if(x == -1){
    printf("%s\n", strerror(errno));
  }
  printf("Successfully changed the directory");
  return currents();
}

void pipe_func(char **args){
  
}
