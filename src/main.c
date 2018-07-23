#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

int main(int argc, char* argv[]) {
  char* line = readline(":>");

  printf("\n%s\n", line);
  
  return EXIT_SUCCESS;
}
