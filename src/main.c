#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"
#include "token_stack.h"

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

typedef struct CalcFunc_s
{
    int argv;
    char* name;
    value (*func)();
} CalcFunc;

int do_func(TokenStack* stack, CalcFunc* func)
{
    if(stack_size(stack) >= func->argv)
    {
        
        push_token(stack,
                   func->func(pop_token(stack),
                              pop_token(stack)));
        return 0;
    }
    else
    {
        return 1;
    }
}

value add(value b, value a)
{
    return a + b;
}

void process_token(char* token, TokenStack* stack)
{
    
    
    //token is a function
    if (strcmp(token, "+") == 0)
    {
        CalcFunc plus_func;
        plus_func.argv = 2;
        plus_func.func = plus;
        
        do_func(stack, &plus_func);
        /* printf("token is +\n"); */
        /* if (stack_size(stack) >= 2) */
        /* { */
        /*     value a = pop_token(stack); */
        /*     value b = pop_token(stack); */
        /*     printf("%g + %g = %g\n", a, b, a + b); */
        /*     push_token(stack, a + b); */
        /* } */
    }
    else if (strcmp(token, "-") == 0)
    {
        if (stack_size(stack) >= 2)
        {
            //we want to do the second to the top, minus the top, so:
            //3 2 - => 1, a b - => (a - b)
            value b = pop_token(stack);
            value a = pop_token(stack);
            push_token(stack, a - b);
        }
    }
    else if (strcmp(token, "*") == 0)
    {
        if (stack_size(stack) >= 2)
        {
        
            value a = pop_token(stack);
            value b = pop_token(stack);
            push_token(stack, a * b);
        }
    }
    else if (strcmp(token, "/") == 0)
    {
        if (stack_size(stack) >= 2)
        {
            //same as minus, take b then a
            value b = pop_token(stack);
            value a = pop_token(stack);
            push_token(stack, a / b);
        }
    }
    else
    {
        //FIXME handle error of parsing
        value val = strtod(token, NULL);
        printf("pushing %f to %u\n", val, stack);
        push_token(stack, val);
    }
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
    }

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
