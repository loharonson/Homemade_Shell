#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  char * cmds[20];
  char line[] = "cowsay -f dragon-and-cow roar";
  int i = parse_args(line,cmds, ";");
  char * args[20];
  int j = parse_args(cmds[0], args, " ");
  execvp(args[0], args);
}
