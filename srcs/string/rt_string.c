#include "rt_string.h"
#include <string.h>

str8 get_next_line(str8 file, u32* curr, t_memory_arena* arena)
{
    str8 out = {NULL, 0};

    if (!curr || !arena || *curr >= file.size)
    {
        return out; // EOF / invalid
    }

    u32 start = *curr;
    u32 i     = start;

    //-- find end of line
    while (i < file.size && file.mem[i] != '\n')
    {
        i++;
    }

    //-- len without '\n'
    u32 len = i - start;

    //-- win capable
    if (len > 0 && file.mem[start + len - 1] == '\r')
    {
        len--;
    }

    //-- we want \0 so we need allocation
    //-- TODO: Switch api on size in str8
    u8* dst = (u8*)arena_push(arena, len + 1);
    if (!dst)
    {
        return out;
    }

    // copy
    if (len > 0)
    {
        memcpy(dst, file.mem + start, len);
    }

    dst[len] = 0;

    out.mem  = dst;
    out.size = len;

    // move cursor after \n
    if (i < file.size && file.mem[i] == '\n')
    {
        i++;
    }

    *curr = i;
    return out;
}
