#ifndef operations_h
  #define operations_h
  char ** redirect_general(char ** args);
  void redirect_stdout_overwrite(char ** args);
  void redirect_stdout_append(char ** args);
  //For now: reditrect_stdin doesn't have a input but at the end we need to make it read from a file in which case we will have a string input
  void redirect_stdin();
  char* currents();
  void changing_dirs(char * desires);
  void pipe_func(char ** args);
#endif
