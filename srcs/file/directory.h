#pragma once

#include "../string/rt_string.h"

typedef struct
{
    void* pl_dir_info;
} t_directory;

str8        next_non_dir_file(t_directory* dir, t_memory_arena* arena);
t_directory open_directory(str8 path, t_memory_arena* arena);
void        close_directory(t_directory* dir);
