#include "stdlib.h"

#include "token_stack.h"

#define STACK_SIZE 32
/*
 * Return a new, initialized token stack.
 */
TokenStack* new_token_stack()
{
    TokenStack* stack = malloc(sizeof(TokenStack));
    stack->top_idx = 0;
    return stack;
}

char* pop_token(TokenStack* stack)
{
    char* result = stack->frames[stack->top_idx].token;
    stack->top_idx -= 1;
    return result;
}

/*
 * Push a token to a stack. 
 */ 
int push_token(TokenStack* stack, char* token)
{
    if (stack->top_idx >= STACK_SIZE)
    {
        return 1;
    }
    stack->top_idx += 1;
    stack->frames[stack->top_idx].token = token;
    return 0;
}
