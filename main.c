#include "main.h"
#include "unistd.h"

int main(){
  char * args[20][128];
  char line[] = "cowsay -f dragon-and-cow roar";
  int i = parse_args(line,args);
  execvp(args[0][0], args[0]);
}
