#include "hash.h"

void init_hash_map(FuncHashMap* map, size_t size)
{
    map->size = size;
    map->map = calloc(size, sizeof(FuncMapEntry));
}

/*
 * This is our hashing function. We CompSci now boys!!!
 */
size_t hash_hash(char* key, size_t size)
{
    size_t hash_val = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash_val += (size_t) key[i];
        hash_val *= i + 2;
    }
    return hash_val % size;
}

/*
 * Put a CalcFunc into a FuncHashMap with a given name. 
 */ 
void hash_put(FuncHashMap* map, char* key, CalcFunc* func)
{
    // hash the key
    size_t hash = hash_hash(key, map->size);
    // make a new map entry
    FuncMapEntry* entry = malloc(sizeof(FuncHashMap));
    entry->name = key;
    entry->func = func;
    // insert it!
    map->map[hash] = entry;
}

/*
 * Get a CalcFunc from a FuncHashMap. 
 */ 
CalcFunc* hash_get(FuncHashMap* map, char* key)
{
    // hash the key
    size_t hash = hash_hash(key, map->size);    
    // access the entry
    FuncMapEntry* entry = map->map[hash];
    // walk the linked list until our key matches
    if (entry == NULL)
    {
        return NULL;
    }
    return entry->func;
}

void delete_map_entries(FuncMapEntry* entry)
{
    if (entry->next != NULL)
    {
        return delete_map_entries(entry->next);
    }
    free(entry);
}

/*
 * Free all the memory allocated for the hashmap
 */ 
void delete(FuncHashMap* map)
{
    //just dont bother, and let the process end. That's your best bet
    for (size_t i = 0; i < map->size; i++)
    {
        if (map->map[i] != NULL)
        {
            //delete the linked list stored here recursively
            delete_map_entries(map->map[i]);
        }
    }
}

