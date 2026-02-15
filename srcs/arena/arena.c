#define _GNU_SOURCE
#include "../includes/MiniRT.h"
#include "arena.h"
#include <sys/mman.h>

void clear_arena(t_memory_arena* arena) { arena->cursor = 0; }

void arena_pop(t_memory_arena* arena, u32 size)
{
    if (size > arena->cursor)
    {
        arena->cursor = 0;
    }
    else
    {
        arena->cursor -= size;
    }
}

void* arena_push(t_memory_arena* arena, u32 size)
{
    if (arena->cursor + size >= arena->size)
    {
        return 0;
    }
    void* return_address = ((u8*)arena->memory) + arena->cursor;
    arena->cursor += size;

    return return_address;
}

void* arena_push_aligned(t_memory_arena* arena, u32 size, u32 aligment)
{
    u32 padding = aligment - (((u64)((u8*)arena->memory + arena->cursor)) % aligment);
    if (arena->cursor + size + padding >= arena->size)
    {
        return 0;
    }
    void* return_address = ((u8*)arena->memory) + arena->cursor + padding;
    arena->cursor += size + padding;

    return return_address;
}

t_memory_arena create_arena(u32 size)
{
    t_memory_arena arena;
    arena.memory = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    arena.size   = size;
    arena.cursor = 0;

    return arena;
}

void destroy_arena(t_memory_arena* arena)
{
    munmap(arena->memory, arena->size);

    arena->size   = 0;
    arena->cursor = 0;
}
