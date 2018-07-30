#ifndef HASH_H
#define HASH_H

#include "stdlib.h"

#include "calc_functions.h"

typedef struct FuncMapEntry_s
{
    struct FuncMapEntry_s* next;
    char* name;
    CalcFunc* func;
} FuncMapEntry;

typedef struct FuncHashMap_s
{
    size_t size;
    // This is an array of pointers (linked lists)
    FuncMapEntry** map;
} FuncHashMap;

size_t hash_hash(char* key, size_t size);
void hash_put(FuncHashMap*, char* name, CalcFunc* func);
CalcFunc* hash_get(FuncHashMap*, char* name);


#endif
