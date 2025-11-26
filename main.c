#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  char *** cmds = malloc(20 * sizeof(char **));
  char line[] = "cowsay -f dragon-and-cow roar";
  int i = parse_cmds(line,cmds);
  printf("%d\n",i);
  execvp(cmds[0][0], cmds[0]);
}
