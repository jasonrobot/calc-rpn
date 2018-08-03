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

int could_be_num(char* str)
{
    double parsed = strtod(str, NULL);
    //if its not a 0, its a number guaranteed
    if (parsed != 0)
    {
        return 1;
    }
    else 
    {
        // if it is a 0
        // if the string contains anything but '-', '0', and '.', its not a true 0
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] != '-' && str[i] != '0' && str[i] != '.')
            {
                return 0;
            }
        }
    }
    // it wasnt 0, but wasn't not 0.......
    return 0;
}

void process_token(char* token, TokenStack* stack, FuncHashMap* function_map)
{
    //try parsing numbers first
    if (could_be_num(token))
    {
        char* err = NULL;
        value val = strtod(token, &err);
        push_token(stack, val);
    }
    else
    {
        //try to parse a function
        CalcFunc *func_ptr = NULL;
        func_ptr = hash_get(function_map, token);
        if (func_ptr != NULL)
        {
            //token is a function
            call_calc_func(func_ptr, stack);
        }
        else
        {
            printf("Undefined symbol: %s\n", token);
        }
    }
    // You shouldn't be here.
}

/*
 * Get a line of input from readline
 *
 * @return the number of tokens read
 */
int get_input(char* line, char** tokens) {
    
    /* printf("\n%s\n", line); */

    int token_count = 0;
    token_count = tokenize(line, tokens);

    if (tokens == NULL)
    {
        printf("failed to parse\n");
        return 0;
    }    

    return token_count;
}

void setup_functions(FuncHashMap* map)
{
    CalcFunc* func = NULL;
    func = make_calc_func(add, 2, 1, "+");
    hash_put(map, func->name, func);

    func = make_calc_func(subtract, 2, 1, "-");      
    hash_put(map, func->name, func);

    func = make_calc_func(multiply, 2, 1, "*");
    hash_put(map, func->name, func);

    func = make_calc_func(divide, 2, 1, "/");
    hash_put(map, func->name, func);

    func = make_calc_func(modulo, 2, 1, "mod");
    hash_put(map, func->name, func);
    
    func = make_calc_func(power, 2, 1, "pow");
    hash_put(map, func->name, func);
    hash_put(map, "^", func);
    hash_put(map, "**", func);

    func = make_calc_func(root, 2, 1, "root");
    hash_put(map, func->name, func);

    func = make_calc_func(square_root, 1, 1, "sqrt");
    hash_put(map, func->name, func);

    func = make_calc_func(swap, 2, 2, "swap");
    hash_put(map, func->name, func);

    func = make_calc_func(drop, 1, 0, "drop");
    hash_put(map, func->name, func);

    func = make_calc_func(drop, 0, 0, "clear");
    hash_put(map, func->name, func);

    func = make_calc_func(dup, 1, 2, "dup");
    hash_put(map, func->name, func);
}

int main(int argc, char* argv[])
{
    #ifdef DEBUG
    printf("you're debugging!\n");
    #endif
    
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
        #ifdef DEBUG
        printf("stack size is %d\n", stack_size(token_stack));
        #endif
        print_stack(token_stack);

        char* line = readline(": ");
        
        if (should_quit(line))
        {
            return EXIT_SUCCESS;
        }
         
        int token_count = get_input(line, tokens);
        if ( token_count > 0)
        {
            for (int i = 0; i < token_count; i++)
            {
                #ifdef DEBUG
                printf("%s\n", tokens[i]);
                #endif
                process_token(tokens[i], token_stack, &function_map);
                free(tokens[i]);
            }

        }
    }

    return EXIT_SUCCESS;
}
