#include "directory.h"
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

typedef struct
{
    DIR*           dir_handle;
    struct dirent* entry;
    char           dir_path[4096];
} t_platform_dir_data;

static int is_directory(const char* dir_path, const char* name)
{
    char full_path[4096];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, name);

    struct stat st;
    if (stat(full_path, &st) == 0)
    {
        return S_ISDIR(st.st_mode);
    }
    return 0;
}

str8 next_non_dir_file(t_directory* dir, t_memory_arena* arena)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    str8                 res  = { NULL, 0 };

    while ((data->entry = readdir(data->dir_handle)) != NULL)
    {
        if (!is_directory(data->dir_path, data->entry->d_name))
        {
            break;
        }
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
    strncpy(data->dir_path, null_term_path, sizeof(data->dir_path) - 1);
    data->dir_path[sizeof(data->dir_path) - 1] = '\0';

    res.pl_dir_info = data;
    return res;
}

void close_directory(t_directory* dir)
{
    t_platform_dir_data* data = dir->pl_dir_info;
    closedir(data->dir_handle);
}
