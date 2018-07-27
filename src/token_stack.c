#include "stdlib.h"

#include "token_stack.h"

#define STACK_SIZE 32

/*
 * Return a new, initialized token stack.
 *
 * @return TokenStack*
 */
TokenStack* new_token_stack()
{
    TokenStack* stack = malloc(sizeof(TokenStack));
    stack->top_idx = 0;
    return stack;
}

/*
 * Pop the token off the top of the stack.
 *
 * @param stack TokenStack* the stack to pop from
 * @return char* the token popped or NULL
 */ 
char* pop_token(TokenStack* stack)
{
    if (stack->top_idx <= 0)
    {
        return NULL;
    }
    
    char* result = stack->frames[stack->top_idx].token;
    stack->top_idx -= 1;
    return result;
}

/*
 * Push a token to a stack.
 *
 * @param stack TokenStack* the stack to push to.
 * @param token char* the token to push on the stack.
 */ 
int push_token(TokenStack* stack, char* token)
{
    if (stack->top_idx >= STACK_SIZE - 1)
    {
        return 1;
    }
    stack->top_idx += 1;
    stack->frames[stack->top_idx].token = token;
    return 0;
}
