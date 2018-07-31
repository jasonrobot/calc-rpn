#include "stdlib.h"
#include "math.h"

#include "token_stack.h"
#include "calc_functions.h"

CalcFunc* make_calc_func(int (*function)(), int argc, int retc, char* name)
{
    CalcFunc* calc_func = malloc(sizeof(CalcFunc));
    calc_func->argc = argc;
    calc_func->retc = retc;
    calc_func->logic = function;
    calc_func->name = name;
    return calc_func;
}

/*
 * Call a CalcFunc with data from a TokenStack. Handles all args and retvals.
 *
 * @param func The func object to call.
 * @param stack The token stack to get args from and put retvals to.
 */ 
void call_calc_func(CalcFunc* func, TokenStack* stack)
{
    value ret_vals[func->retc];
    /* int error = func->logic(pop_token(stack), pop_token(stack), &ret_vals); */
    //TODO handle too few args
    if (func->argc > stack_size(stack))
    {
        //TODO error here
        return;
    }
    //TODO default to some error state
    int error = 0;
    switch(func->argc)
    {
    case 0:
        error = call_0(func->logic, stack, ret_vals);
        break;
    case 1:
        error = call_1(func->logic, stack, ret_vals);
        break;
    case 2:
        error = call_2(func->logic, stack, ret_vals);
        break;
    case 3:
        error = call_3(func->logic, stack, ret_vals);
        break;
    case 4:
        error = call_4(func->logic, stack, ret_vals);
        break;
    default:
        break;
    }
    if (error)
    {
        //TODO handle error
    }
    for (int i = 0; i < func->retc; i++)
    {
        push_token(stack, ret_vals[i]);
    }
}

int add(value a, value b, value* ret)
{
    *ret = a + b;
    return EXIT_SUCCESS;
}

int subtract(value a, value b, value* ret)
{
    *ret = a - b;
    return EXIT_SUCCESS;
}

int multiply(value a, value b, value* ret)
{
    *ret = a * b;
    return EXIT_SUCCESS;
}

int divide(value a, value b, value* ret)
{
    *ret = a / b;
    return EXIT_SUCCESS;
}

int modulo(value a, value b, value* ret)
{
    if (a != floor(a) || b != floor(b))
    {
        return EXIT_FAILURE;
    }
    *ret = (int) floor(a) % (int) floor(b);
    return EXIT_SUCCESS;
}

int power(value a, value b, value* ret)
{
    *ret = pow(a, b);
    return EXIT_SUCCESS;
}

int root(value a, value b, value* ret)
{
    *ret = pow(a, -b);
    return EXIT_SUCCESS;
}

int square_root(value a, value* ret)
{
    *ret = sqrt(a);
    return EXIT_SUCCESS;
}

int swap(value a, value b, value* ret)
{
    ret[0] = b;
    ret[1] = a;
    return EXIT_SUCCESS;
}

/*
 * An empty function used for dropping values.
 * Will drop any number of args, just specify how many in argc of the CalcFunc
 */ 
int drop()
{
    //doesnt actually do anything
    return EXIT_SUCCESS;
}

int dup(value a, value* ret)
{
    ret[0] = a;
    ret[1] = a;
    return EXIT_SUCCESS;
}
