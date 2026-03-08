#pragma once

#include "../arena/arena.h"
#include "../includes/my_types.h"

typedef struct s_str8
{
    u8* mem;
    u32 size;
} str8;

str8 get_next_line(str8 file, u32* curr, t_memory_arena* arena);
