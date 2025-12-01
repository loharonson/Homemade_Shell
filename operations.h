#ifndef operations_h
  #define operations_h
  void redirect_stdout_overwrite(char ** args);
  void redirect_stdout_append(char ** args);
  void redirect_stdin(char ** args);
  void pipe(char ** args);
#endif
