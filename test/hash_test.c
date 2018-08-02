#pragma GCC diagnostic ignored "-Wunused-function"

#include "check.h"
#include "stdio.h"

#include "../src/hash.h"

START_TEST(test_hash_function)
{
    size_t result = 0;
    result = hash_hash("foobar", 16);
    size_t result_2 = hash_hash("foobar", 16);
    ck_assert_uint_eq(result, result_2);
    
    result_2 = hash_hash("qwerty", 16);
    ck_assert_uint_ne(result, result_2);
}
END_TEST

START_TEST(test_hash_function_doesnt_suck)
{
    size_t result = hash_hash("as", 64);
    size_t result_2 = hash_hash("sa", 64);
    ck_assert_uint_ne(result, result_2);

    result = hash_hash("x", 64);
    ck_assert_uint_ne(result, 0);
}
END_TEST

START_TEST(test_create_map)
{
    // I mean... there's no ctor
}
END_TEST

START_TEST(test_basic_usage)
{
    FuncHashMap map;
    init_hash_map(&map, 64);

    CalcFunc func;
    char* name = "function";

    hash_put(&map, name, &func);
    CalcFunc* result = hash_get(&map, name);
    ck_assert_ptr_eq(&func, result);
}
END_TEST

START_TEST(test_insert_same_key)
{}
END_TEST

/*
 * This might be kinda hard to force a collision, but what the heck /shrug
 * Maybe we just supply a fake hash function
 */ 
START_TEST(test_insert_collision)
{}
END_TEST

START_TEST(test_get_unset_key)
{
    FuncHashMap map;
    init_hash_map(&map, 64);
    
    CalcFunc* result = hash_get(&map, "foobar");
    ck_assert_ptr_null(result);
}
END_TEST

/*
 * Can fake this by directly setting some colliding keys in the map
 * Alternatively, we could still redefine the hash function
 */ 
START_TEST(test_get_collided_hashes)
{}
END_TEST

/*
 * Dont know how to check for memory usage/leaks, but we can at least
 * test that the functions work.
 */
START_TEST(test_delete_hash)
{}
END_TEST
