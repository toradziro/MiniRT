#pragma once

#include "../includes/my_types.h"
#include "../arena/arena.h"

typedef struct s_str8
{
    u32     size;
    u8*     mem;
} str8;

str8 get_next_line(str8 file, u32* curr, t_memory_arena* arena);
