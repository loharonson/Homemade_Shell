#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdin.h>

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

void readingstuff(){
  int x = open(stdin, O_RDONLY);

}
