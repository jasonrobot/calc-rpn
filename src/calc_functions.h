#ifndef CALC_FUNCTIONS_H
#define CALC_FUNCTIONS_H

#include "token_stack.h"

#define call_0(action, stack, ret_vals) action(ret_vals);
#define call_1(action, stack, ret_vals) action(pop_token(stack), ret_vals);
#define call_2(action, stack, ret_vals) action(pop_token(stack), pop_token(stack), ret_vals);
#define call_3(action, stack, ret_vals) action(pop_token(stack), pop_token(stack), pop_token(stack), ret_vals);
#define call_4(action, stack, ret_vals) action(pop_token(stack), pop_token(stack), pop_token(stack), pop_token(stack), ret_vals);

typedef struct CalcFunc_s
{
    char* name;
    int argc;
    int retc;
    /* value retv[16]; */
    int (*logic)();
} CalcFunc;

int add(value, value, value*);
int swap(value, value, value*);

#endif
