#ifndef operations_h
  #define operations_h
  char ** redirect_general(char ** args);
  void redirect_stdout_overwrite(char ** args);
  void redirect_stdout_append(char ** args);
  void redirect_stdin(char ** args);
  void pipe_func(char ** args);
#endif
