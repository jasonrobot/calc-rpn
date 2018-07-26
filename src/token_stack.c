#include "stdlib.h"

#define STACK_SIZE 32

typedef struct TokenStackFrame_s
{
    char* token;
} TokenStackFrame;

typedef struct TokenStack_s
{
    TokenStackFrame* top;
    TokenStackFrame frames[STACK_SIZE];
} TokenStack;

/*
 * Return a new, initialized token stack.
 */
TokenStack new_token_stack()
{
    TokenStack stack;
    stack.top = stack.frames;
    return stack;
}

char* pop_token(TokenStack stack)
{
    char* result = stack.top->token;
    stack.top = stack.top - sizeof(TokenStackFrame);
    return result;
}

int push_token(TokenStack stack, char* token)
{
    
}
