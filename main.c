#include "main.h"
#include "operations.h"
#include <errno.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int err() {
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

int main(int argc, char *argv[]) {
  while (1) {
    if (argc == 1 || strcmp(argv[1], "-n")) {
      char cwd[PATH_MAX];
      char *home = getenv("HOME");
      getcwd(cwd, sizeof(cwd));
      if (strncmp(cwd, home, strlen(home)) == 0) {
        printf("~%s$ ", cwd + strlen(home));
      } else {
        printf("%s$ ", cwd);
      }
      fflush(stdout);
    }
    // read, then parse, then execvp
    char *line = readingline();
    char *cmds[20];
    int cmds_amt = parse_args(line, cmds, ";");
    for (int i = 0; i < cmds_amt; i++) {
      char *args[20];
      char *parse_cmd = malloc(BUFFER_SIZE);
      strcpy(parse_cmd, cmds[i]);
      if (!strcmp(cmds[i], "exit")) {
        printf("Goodbye!\n");
        exit(0);
      }
      int j = parse_args(parse_cmd, args, " ");
      // handling of cd below
      int cd_success = 1;
      if (!strcmp(args[0], "cd")) {
        char *new_dir = changing_dirs(args[1]);
        if (new_dir) {
          printf("%s\n", new_dir);
          free(new_dir);
        }
        // exit(0);
        cd_success = 0;
      }
      // handling of cd above

      if (cd_success  == 1) {
        int p = fork();
        if (p == -1)
          err();
        if (p == 0) {
          if (j == 0) {
            exit(0);
          }
          int specials = 0;
          // check for special symbols
          if (strchr(cmds[i], '<')) {
            specials++;
            redirect_stdin(args, j);
            exit(0);
          }
          if (strchr(cmds[i], '|')) {
            specials++;
            pipe_func(args);
            exit(0);
          }
          if (strchr(cmds[i], '>')) {
            specials++;
            if (strstr(cmds[i], ">>")) {
              redirect_stdout(args, 1, j);
            } else {
              redirect_stdout(args, 0, j);
            }
            exit(0);
          }
          if (specials == 0) {
            execvp(args[0], args);
          }
          exit(0);
        }
      }
      int status;
      pid_t exit_child = wait(&status);
      if (exit_child == -1)
        err();
      if (WIFEXITED(status))
        continue;
    }
  }
}
