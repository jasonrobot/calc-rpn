/*
 * token_stack represents a stack of tokens to do calculations with 
 */ 

#define STACK_SIZE 32

typedef double value;

typedef struct TokenStackFrame_s
{
    value token;
} TokenStackFrame;

typedef struct TokenStack_s
{
    int top_idx;
    TokenStackFrame frames[STACK_SIZE];
} TokenStack;

TokenStack* new_token_stack();
value pop_token(TokenStack* stack);
int push_token(TokenStack* stack, value token);
int stack_size(TokenStack* stack);
void print_stack(TokenStack* stack);
