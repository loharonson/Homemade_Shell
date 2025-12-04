#include "main.h"
#include "operations.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

int main(int argc, char * argv[]){
  while(1){
    if(argc == 1 || strcmp(argv[1], "-n")){
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
    }
    //read, then parse, then execvp
    char * line = readingline();
    if(!line){
      printf("Goodbye!\n");
      exit(0);
    }
    printf("line: %s\n", line);
    char * cmds[20];
    int cmds_amt = parse_args(line, cmds, ";");
    printf("%d\n", cmds_amt);
    printf("%s\n", cmds[0]);
    for(int i = 0; i < cmds_amt; i++){
      char * args[20];
      int j = parse_args(cmds[i], args, " ");
      int p = fork();
      if(p == -1)err();
      if(p == 0){
        if(!strcmp(args[0], "cd")){
          changing_dirs(args[1]);
          exit(0);
        }
        int specials = 0;
        //check for special symbols
        if(strchr(cmds[i], '>')){
          specials++;
          if(strstr(cmds[i], ">>")){
            redirect_stdout(args, 0, j);
          }
          else{
            redirect_stdout(args, 1, j);
          }
        }
        if(strchr(cmds[i], '|')){
          specials++;
          pipe_func(args);
        }
        if(strchr(cmds[i],'<')){
          specials++;
          redirect_stdin(args);

        }
        execvp(args[0], args);
        exit(0);
      }
      int status;
      pid_t exit_child = wait(&status);
      if(exit_child == -1)err();
      if(WIFEXITED(status))continue;
    }
  }
}
