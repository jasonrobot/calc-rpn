#include "check.h"
#include "stdio.h"

#include "../src/token_stack.h"

START_TEST (token_stack_test)
{
    printf("hello?\n");
}
END_TEST

START_TEST (token_stack_push)
{
    TokenStack* stack = new_token_stack();
    push_token(stack, "foobar");
    ck_assert_int_eq(stack->top_idx, 1);
}
END_TEST
