#include "directory.h"
#include <dirent.h>
#include <string.h>

typedef struct
{
    DIR*           dir_handle;
    struct dirent* entry;
} t_platform_dir_data;

str8 next_non_dir_file(t_directory* dir, t_memory_arena* arena)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    str8                 res  = { NULL, 0 };

    data->entry = readdir(data->dir_handle);
    while (data->entry && data->entry->d_type == DT_DIR)
    {
        data->entry = readdir(data->dir_handle);
    }
    if (data->entry)
    {
        res.size = strlen(data->entry->d_name);
        res.mem  = arena_push(arena, res.size);
        for (u32 i = 0; i < res.size; ++i)
        {
            res.mem[i] = data->entry->d_name[i];
        }
    }
    return res;
}

t_directory open_directory(str8 path, t_memory_arena* arena)
{
    t_directory res;
    char        null_term_path[4096];

    for (u32 i = 0; i < path.size; ++i)
    {
        null_term_path[i] = path.mem[i];
    }
    null_term_path[path.size] = '\0';

    t_platform_dir_data* data = arena_push(arena, sizeof(t_platform_dir_data));
    data->dir_handle          = opendir(null_term_path);
    data->entry               = NULL;
    res.pl_dir_info           = data;

    return res;
}

void close_directory(t_directory* dir)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    closedir(data->dir_handle);
}
