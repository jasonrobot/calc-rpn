#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"

int main(int argc, char* argv[]) {
  char* line = readline(":>");

  printf("\n%s\n", line);

  char** tokens = malloc(sizeof(char*) * 256);
  int token_count = 0;
  token_count = tokenize(line, tokens);

  if (tokens == NULL) {
      printf("failed to parse\n");
      /* return EXIT_FAILURE; */
  }

  for (int i = 0; i < token_count; i++)
  {
      printf("%s\n", tokens[i]);
  }
  
  return EXIT_SUCCESS;
}
