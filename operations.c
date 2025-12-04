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
  dup2(x, STDIN_FILENO);
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
char * changing_dirs(char * desires){
  currents();
  int x = chdir(desires);
  if(x == -1){
    printf("%s\n", strerror(errno));
    return currents();
  }
  printf("Successfully changed the directory");
  return currents();
}

void pipe_func(char **args){
    char *left = strsep(args, "|");
    FILE *outputs = popen(left, "r");
    if (outputs == NULL) err();
    int tmp = open("midst.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (tmp < 0) err();
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), outputs) != NULL) {
        write(tmp, buffer, strlen(buffer));
    }
    pclose(outputs);
    close(tmp);
    pid_t pid = fork();
    if (pid == 0) {
        int in = open("midst.txt", O_RDONLY);
        if (in < 0) err();
        dup2(in, STDIN_FILENO);
        close(in);

        execvp(args[0], args);
        err();
    } else {
        waitpid(pid, NULL, 0);
        remove("midst.txt");
    }
}
