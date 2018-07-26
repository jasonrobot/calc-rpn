#include "stdlib.h"
#include "string.h"

/*
 * Split an input string into an array of token strings.
 *
 * @param _input_string the input to tokenize
 * @param dest destination array to store tokens into.
 * @param max_tokens maximum amount of tokens to accept
 *
 * @return amount of tokens parsed
 */
int tokenize(const char* _input_string, char** dest, int max_tokens) {
    // create a local, dont modify args
    // FIXME you're risking memory leaks, yo!
    char* input_string = malloc(sizeof(_input_string));
    strcpy(input_string, _input_string);
    
    // track the sizes of our input, to return the minimum data
    int token_count = 0;

    char* token;
    token = strtok(input_string, " ");
    if (token == NULL)
    {
        free(input_string);
        return 0;
    }
    // start token count at 1, since we've got our first
    for (; token != NULL; token_count++)
    {
        dest[token_count] = malloc(sizeof(char) + strlen(token));
        strcpy(dest[token_count], token);

        if (token_count == max_tokens)
        {
            break;
        }
        
        token = strtok(NULL, " ");
    }

    // free our temps
    free(input_string);
    
    return token_count;
}
