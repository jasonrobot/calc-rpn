#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"

int should_quit(char* input)
{
    // we got EOF, quit
    if (input == NULL)
    {
        return 1;
    }
        
    if (strlen(input) == 0)
    {
        return 0;
    }

    if (input[0] == 'q')
    {
        return 1;
    }

    return 0;
}

/*
 * Get a line of input from readline
 *
 * @return boolean whether or not to quit
 */
int get_input() {
    char* line = readline(": ");

    if (should_quit(line))
    {
        return 1;
    }
    
    printf("\n%s\n", line);

    char** tokens = malloc(sizeof(char*) * 256);
    int token_count = 0;
    token_count = tokenize(line, tokens);

    if (tokens == NULL)
    {
        printf("failed to parse\n");
        /* return EXIT_FAILURE; */
    }

    for (int i = 0; i < token_count; i++)
    {
        printf("%s\n", tokens[i]);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int quit;
    do
    {
        quit = get_input();
    } while (quit == 0);
  
    return EXIT_SUCCESS;
}
