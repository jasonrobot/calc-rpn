#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"
#include "token_stack.h"
#include "calc_functions.h"

enum CalcError
{
    NUMBER_PARSE_ERROR,
    INVALID_FUNCTION_ERROR,
    TOO_FEW_ARGS_ERROR,
};

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

void process_token(char* token, TokenStack* stack)
{
    CalcFunc func;

    //token is a function
    if (strcmp(token, "+") == 0)
    {
        make_calc_func(&func, add, 2, 1);      
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "-") == 0)
    {
        make_calc_func(&func, subtract, 2, 1);      
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "*") == 0)
    {
        make_calc_func(&func, multiply, 2, 1);      
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "/") == 0)
    {
        make_calc_func(&func, divide, 2, 1);      
        call_calc_func(&func, stack);        
    }
    else if (strcmp(token, "swap") == 0)
    {
        make_calc_func(&func, swap, 2, 1);      
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "drop") == 0)
    {
        make_calc_func(&func, drop, 1, 0);
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "clear") == 0)
    {
        make_calc_func(&func, drop, stack_size(stack), 0);      
        call_calc_func(&func, stack);
    }
    else if (strcmp(token, "dup") == 0)
    {
        make_calc_func(&func, dup, 1, 2);
        call_calc_func(&func, stack);        
    }
    else
    {
        //FIXME handle error of parsing
        char* err = NULL;
        value val = strtod(token, &err);
        if (err == NULL)
        {
            printf("Unable to parse %s as a number", token);
        }
        else
        {
            /* printf("pushing %f to %u\n", val, stack); */
            push_token(stack, val);
        }
    }
    // You shouldn't be here.
}

/*
 * Get a line of input from readline
 *
 * @return boolean whether or not to quit
 */
int get_input(TokenStack* stack) {
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
        process_token(tokens[i], stack);
        free(tokens[i]);
    }

    free(tokens);

    return 0;
}

int main(int argc, char* argv[])
{
    // set up all the initial variables
    int quit = 0;
    TokenStack* token_stack = new_token_stack();

    while (quit == 0)
    {
        printf("stack size is %d\n", stack_size(token_stack));
        print_stack(token_stack);
        quit = get_input(token_stack);
    }

    return EXIT_SUCCESS;
}
