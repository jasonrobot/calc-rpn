#include "stdlib.h"

#include "token_stack.h"

int add(value b, value a, value* ret)
{
    *ret = a + b;
    return EXIT_SUCCESS;
}

int swap(value a, value b, value* ret)
{
    ret[0] = b;
    ret[1] = a;
    return EXIT_SUCCESS;
}
