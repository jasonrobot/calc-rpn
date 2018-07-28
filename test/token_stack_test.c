#pragma GCC diagnostic ignored "-Wunused-function"

#include "check.h"
#include "stdio.h"

#include "../src/token_stack.h"

START_TEST (token_stack_test)
{
    TokenStack* stack = new_token_stack();
    push_token(stack, 123);
    ck_assert_int_eq(stack->top_idx, 1);
    
    value output = pop_token(stack);
    ck_assert_int_eq(stack->top_idx, 0);
    ck_assert_double_eq(output, 123);
}
END_TEST

START_TEST (stack_overflow_test)
{
    TokenStack* stack = new_token_stack();
    int i = 0;
    for (; i < STACK_SIZE; i++)
    {
        push_token(stack, 69);
    }
    ck_assert_int_eq(i, STACK_SIZE);
    ck_assert_int_eq(stack->top_idx, STACK_SIZE - 1);

    int result = push_token(stack, 69);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST (pop_empty_stack)
{
    TokenStack* stack = new_token_stack();
    value result = pop_token(stack);

    ck_assert_int_eq(stack->top_idx, 0);
    /* ck_assert_ptr_null(result); */
}
END_TEST
