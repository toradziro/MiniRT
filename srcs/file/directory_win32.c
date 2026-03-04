#include "directory.h"
#include "windows.h"
#include <stdio.h>

typedef struct
{
    WIN32_FIND_DATAA    find_data;
    HANDLE              h_find;
} t_platform_dir_data;

str8 next_non_dir_file(t_directory* dir, t_memory_arena* arena)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    str8 res = { NULL, 0 };
    BOOL find_res;
    find_res = FindNextFileA(data->h_find, &data->find_data);
    while (!!(data->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && find_res)
    {
        find_res = FindNextFileA(data->h_find, &data->find_data);
    }
    if (find_res)
    {
        res.size = strlen(data->find_data.cFileName);
        res.mem = arena_push(arena, res.size);
        for (u32 i = 0; i < res.size; ++i)
        {
            res.mem[i] = data->find_data.cFileName[i];
        }
    }
    return res;
}

t_directory open_directory(str8 path, t_memory_arena* arena)
{
    t_directory res;
    char search_path[MAX_PATH];
    for (u32 i = 0; i < path.size; ++i)
    {
        search_path[i] = path.mem[i];
    }
    search_path[path.size] = '*';
    search_path[path.size + 1] = '\0';

    t_platform_dir_data* data = arena_push(arena, sizeof(t_platform_dir_data));
    data->h_find = FindFirstFileA(search_path, &data->find_data);
    res.pl_dir_info = data;

    return res;
}

void close_directory(t_directory* dir)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    FindClose(data->h_find);
}
