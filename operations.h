#ifndef operations_h
  #define operations_h
  int err();
  void redirect_stdout(char ** args, int is_append, int len);
  void redirect_stdin(char ** args, int len);
  char* currents();
  char * changing_dirs(char * desires);
  void pipe_func(char **args, int len);
#endif
