#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char cwd[PATH_MAX];
	char *home = getenv("HOME");
	getcwd(cwd, sizeof(cwd));
	if(strncmp(cwd, home, strlen(home)) == 0){
    	printf("~%s$\n", cwd + strlen(home));
    } 
    else{
    	printf("%s$\n", cwd);
    }
}
