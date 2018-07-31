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

CalcFunc* make_calc_func(int (*function)(), int argc, int retc, char* name);
void call_calc_func(CalcFunc* func, TokenStack* stack);

int add(value, value, value*);
int subtract(value, value, value*);
int multiply(value, value, value*);
int divide(value, value, value*);
int modulo(value, value, value*);
int power(value, value, value*);
int root(value, value, value*);
int square_root(value, value*);

int swap(value, value, value*);
int drop();
int dup(value, value*);

#endif
