#include "stdlib.h"
#include "stdio.h"

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
 * @return value the token popped or NULL
 */ 
value pop_token(TokenStack* stack)
{
    if (stack->top_idx <= 0)
    {
        //FIXME should error
        return 0;
    }
    
    value result = stack->frames[stack->top_idx].token;
    stack->top_idx -= 1;
    return result;
}

/*
 * Push a token to a stack.
 *
 * @param stack TokenStack* the stack to push to.
 * @param token value the token to push on the stack.
 */ 
int push_token(TokenStack* stack, value token)
{
    if (stack->top_idx >= STACK_SIZE - 1)
    {
        return 1;
    }
    stack->top_idx += 1;
    stack->frames[stack->top_idx].token = token;
    return 0;
}

int stack_size(TokenStack* stack)
{
    return stack->top_idx;
}

void print_stack(TokenStack* stack)
{
    printf("stack: ");
    for (int i = 0; i <= stack->top_idx; i++)
    {
        printf("%f ", stack->frames[i].token);
    }
}
