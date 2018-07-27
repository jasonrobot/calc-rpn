#pragma GCC diagnostic ignored "-Wunused-function"

#include "check.h"
#include "stdio.h"

#include "../src/token_stack.h"

START_TEST (token_stack_test)
{
    TokenStack* stack = new_token_stack();
    push_token(stack, "foobar");
    ck_assert_int_eq(stack->top_idx, 1);
    
    char* output = pop_token(stack);
    ck_assert_int_eq(stack->top_idx, 0);
    ck_assert_str_eq(output, "foobar");
}
END_TEST

START_TEST (stack_overflow_test)
{
    TokenStack* stack = new_token_stack();
    int i = 0;
    for (; i < STACK_SIZE; i++)
    {
        push_token(stack, "x");
    }
    ck_assert_int_eq(i, STACK_SIZE);
    ck_assert_int_eq(stack->top_idx, STACK_SIZE - 1);

    int result = push_token(stack, "x");
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST (pop_empty_stack)
{
    TokenStack* stack = new_token_stack();
    char* result = pop_token(stack);

    ck_assert_int_eq(stack->top_idx, 0);
    ck_assert_ptr_null(result);
}
END_TEST
