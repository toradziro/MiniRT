#pragma once

#include "../includes/my_types.h"

#define Bytes(x) ((size_t)(x))
#define KB(x)    (1024u * Bytes(x))
#define MB(x)    (1024u * KB(x))
#define GB(x)    (1024u * MB(x))

typedef struct s_memory_arena
{
    void*   memory;
    u32     size;
    u32     cursor;
} t_memory_arena;

t_memory_arena create_arena(u32 size);
void    clear_arena(t_memory_arena* arena);
void    arena_pop(t_memory_arena* arena, u32 size);
void*   arena_push(t_memory_arena* arena, u32 size);
void    destroy_arena(t_memory_arena* arena);
