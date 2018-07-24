#include "stdlib.h"
#include "string.h"

/**
 * Split an input string into an array of token strings.
 */
int tokenize(const char* _input_string, char** dest) {
    //create a local, dont modify args
    char* input_string = malloc(sizeof(_input_string));
    strcpy(input_string, _input_string);
    // I dunno, I guess a good max token size is like 32 chars,
    // thats way beyond MAX_INT
    // And we probably wont have more than like 256 tokens
    /* char** tmp = malloc(sizeof(char) * 32 * 256); */
    /* dest = (char**) malloc(sizeof(char*) * 256); */
    
    //track the sizes of our input, to return the minimum data
    int token_count = 0;

    char* token;
    token = strtok(input_string, " ");
    if (token == NULL)
    {
        return 0;
    }
    // start token count at 1, since we've got our first
    for (; token != NULL; token_count++)
    {
        dest[token_count] = malloc(sizeof(char) + strlen(token));
        strcpy(dest[token_count], token);
        token = strtok(NULL, " ");
    }

    //free our temps
    /* free(tmp); */
    free(input_string);
    
    return token_count;
}
