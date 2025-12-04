[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ftjYgND9)
# Systems Project2 - MyShell
Louis Oh-Aronson, Amrit Das, and Solomon Binyaminov

Oh, Das! (ich) Bin.
## Features
Our shell contains many parts that, hopefully, come together to produce a nice, working shell.
Features:
* prompting (include shell path, and flush) - working
* reading the code from the stdin prompts - working
* parsing (include semicolons) - working
* forking --> execvp or internal shell commands, then wait until subprogram exits. exiting as well - working
* <, >, and >> redirection - working
* pipes
* chaining redirects/pipes/both
* cd - attempted, didn't finish implementing- broken

## Function Headers and File Names
In main.c:
* err()
* int main(int argc, char * argv)

In operations.c:
* int err()
* void redirect_stdout(char ** args, int is_append, int len)
* void redirect_stdin(char ** name)
* char* currents()
* char * changing_dirs(char ** desires)
* void pipe_func(char **args)

In parse.c:
* int parse_args( char * line, char ** arg_ary, char * delimiter)

In reading.c:
* char* readingline()
