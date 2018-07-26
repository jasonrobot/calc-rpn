/*
 * token_stack represents a stack of tokens to do calculations with 
 */ 

typedef struct TokenStackFrame_s TokenStackFrame;
typedef struct TokenStack_s TokenStack;

TokenStack new_token_stack();
char* pop_token(TokenStack stack);
int push_token(TokenStack stack, char* token);
