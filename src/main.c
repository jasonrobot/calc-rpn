#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"

int main(int argc, char* argv[]) {
  char* line = readline(":>");

  printf("\n%s\n", line);

  char** tokens = NULL;
  int token_count = 0;
  token_count = tokenize(line, tokens);

  for (int i = 0; i < token_count; i++)
  {
      printf("%s\n", tokens[i]);
  }
  
  return EXIT_SUCCESS;
}
