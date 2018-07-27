/*
 * token_stack represents a stack of tokens to do calculations with 
 */ 

#define STACK_SIZE 32

typedef struct TokenStackFrame_s
{
    char* token;
} TokenStackFrame;

typedef struct TokenStack_s
{
    int top_idx;
    TokenStackFrame frames[STACK_SIZE];
} TokenStack;

TokenStack* new_token_stack();
char* pop_token(TokenStack* stack);
int push_token(TokenStack* stack, char* token);
