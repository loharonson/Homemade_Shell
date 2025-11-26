#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>

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
}
