#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdin.h>
#include <stdout.h>
#include <sys/wait.h>
#include <fcntl.h>

void redirectionout(){
    int x = open("outputting.txt", O_WRONLY| O_APPEND| O_CREAT, 0644)
    File *f;
    char buffer[200];
    while(fgets(buffer,sizeof(buffer), f) != NULL){
        write(x, &buffer, sizeof(buffer));
    }
    //have to add stuff about the exit status
}