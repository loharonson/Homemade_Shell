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
    	printf("~%s$ ", cwd + strlen(home));
    }
    else{
    	printf("%s$ ", cwd);
    }
    fflush(stdout);
    char prompt[ARG_MAX];
    scanf("%s", prompt);
<<<<<<< Updated upstream
=======
    
>>>>>>> Stashed changes
}
