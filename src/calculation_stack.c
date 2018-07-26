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

