#include "stdlib.h"
#include "stdio.h"
#include "readline/readline.h"

#include "tokenize.h"
#include "token_stack.h"
#include "calc_functions.h"

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

void call_calc_func(CalcFunc* func, TokenStack* stack)
{
    value ret_vals[func->retc];
    /* int error = func->logic(pop_token(stack), pop_token(stack), &ret_vals); */
    //TODO handle too few args
    if (func->argc > stack_size(stack))
    {
        return;
    }
    //TODO default to some error state
    int error = 0;
    switch(func->argc)
    {
    case 0:
        error = call_0(func->logic, stack, ret_vals);
        break;
    case 1:
        error = call_1(func->logic, stack, ret_vals);
        break;
    case 2:
        error = call_2(func->logic, stack, ret_vals);
        break;
    case 3:
        error = call_3(func->logic, stack, ret_vals);
        break;
    case 4:
        error = call_4(func->logic, stack, ret_vals);
        break;
    default:
        break;
    }
    if (error)
    {
        //TODO handle error
    }
    for (int i = 0; i < func->retc; i++)
    {
        push_token(stack, ret_vals[i]);
    }
}

void process_token(char* token, TokenStack* stack)
{    
    //token is a function
    if (strcmp(token, "+") == 0)
    {
        CalcFunc plus_func;
        plus_func.argc = 2;
        plus_func.retc = 1;
        plus_func.logic = add;
        
        call_calc_func(&plus_func, stack);
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
    else if (strcmp(token, "swap") == 0)
    {
        CalcFunc swap_func;
        swap_func.argc = 2;
        swap_func.retc = 2;
        swap_func.logic = swap;

        call_calc_func(&swap_func, stack);
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
