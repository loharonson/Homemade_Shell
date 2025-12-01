#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

int main(){
	char cwd[PATH_MAX];
	char *home = getenv("HOME");
	getcwd(cwd, sizeof(cwd));
	if(strncmp(cwd, home, strlen(home)) == 0){
    	printf("~%s$ ", cwd + strlen(home));
  }
  else{
  	printf("%s$ ", cwd);
  }
  fflush(stdout);
  char prompt[ARG_MAX];
  scanf("%s", prompt);
  char * cmds[20];
  char line[] = "cowsay -f dragon-and-cow roar";
  int i = parse_args(line,cmds, ";");
  char * args[20];
  int j = parse_args(cmds[0], args, " ");
  execvp(args[0], args);
    else{
    	printf("%s$ ", cwd);
    }
    fflush(stdout);
    char prompt[ARG_MAX];
    scanf("%s", prompt);
  else{
    printf("%s$ ", cwd);
  }
  fflush(stdout);
  char prompt[ARG_MAX];
  scanf("%s", prompt);

  //read, then parse, then execvp
  char * line = readingline();
  char * cmds[20];
  int cmds_amt = parse_args(line, cmds, ";");
  for(int i = 0; i < cmds_amt; i++){
    char * args[20];
    int j = parse_args(cmds[i], args, " ");
    int p = fork();
    if(p == -1)err();
    if(p == 0){
      //check for special symbols
      if(strchr(cmds[i], '|')){
        pipe(args);
      }
      if(strchr(cmds[i],'<')){
        redirect_stdin(args);
      }
      if(strchr(cmds[i], '>')){
        if(strstr(cdms[i], ">>")){
          redirect_stdout_append(args);
        }
        else{
          redirect_stdout_overwrite(args);
        }
      }
      exit(0);
    }
    int status;
    pid_t exit_child = wait(&status);
    if(exit_child == -1)err();
    if(WIFEXITED(status))continue;
  }
}
