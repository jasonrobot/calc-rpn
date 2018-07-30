#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"
#include "token_stack.h"
#include "calc_functions.h"
#include "hash.h"

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

void process_token(char* token, TokenStack* stack, FuncHashMap* function_map)
{

    CalcFunc *func_ptr = NULL;
    func_ptr = hash_get(function_map, token);
    if (func_ptr != NULL)
    {
        //token is a function
        call_calc_func(func_ptr, stack);
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
 * @return the number of tokens read
 */
int get_input(char** tokens) {
    char* line = readline(": ");
    
    printf("\n%s\n", line);

    int token_count = 0;
    token_count = tokenize(line, tokens);

    if (tokens == NULL)
    {
        printf("failed to parse\n");
        /* return EXIT_FAILURE; */
        return 0;
    }    

    return token_count;
}

void setup_functions(FuncHashMap* map)
{
    CalcFunc* func = NULL;
    func = make_calc_func(add, 2, 1);      
    hash_put(map, "+", func);
    
    func = make_calc_func(subtract, 2, 1);      
    hash_put(map, "-", func);

    func = make_calc_func(multiply, 2, 1);      
    hash_put(map, "*", func);

    func = make_calc_func(divide, 2, 1);      
    hash_put(map, "/", func);

    func = make_calc_func(swap, 2, 2);      
    hash_put(map, "swap", func);

    func = make_calc_func(drop, 1, 0);      
    hash_put(map, "drop", func);

    func = make_calc_func(drop, 0, 0);
    hash_put(map, "clear", func);

    func = make_calc_func(dup, 1, 2);      
    hash_put(map, "dup", func);
}

int main(int argc, char* argv[])
{
    // set up all the initial variables
    int quit = 0;
    TokenStack* token_stack = new_token_stack();
    FuncHashMap function_map;
    init_hash_map(&function_map, 512);

    setup_functions(&function_map);

    while (quit == 0)
    {
        //if you're inputting more than 256 tokens at a time, I pity you
        char* tokens[256];
        printf("stack size is %d\n", stack_size(token_stack));
        print_stack(token_stack);
        
        int token_count = get_input(tokens);
        if (should_quit(tokens[0]))
        {
            return EXIT_SUCCESS;
        }
        if ( token_count > 0)
        {
            for (int i = 0; i < token_count; i++)
            {
                printf("%s\n", tokens[i]);
                process_token(tokens[i], token_stack, &function_map);
                free(tokens[i]);
            }

        }
    }

    return EXIT_SUCCESS;
}
