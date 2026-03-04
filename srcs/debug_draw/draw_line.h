#pragma once

#include "../includes/my_types.h"

typedef struct
{
    i32 x;
    i32 y;
} iv2;

void draw_line(iv2 a, iv2 b, void* pixels, t_color color, i32 width, i32 height);
