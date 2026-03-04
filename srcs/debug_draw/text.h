#pragma once

#include "../string/rt_string.h"
#include "../color/color.h"
#include "draw_line.h"

void draw_debug_text(
    str8 string,
    iv2 location,
    t_color color,
    float scale,      // Overall scale. Default to 1.0f
    float width,      // Width. Default to 1.0f
    float height,     // Height. Default to 1.0f
    float spacing,    // Character Spacing. Default to 0.0f
    float lineheight,  // Line Spacing. Default to 1.0f
    i32 screen_width,
    i32 screen_height,
    void* pixels);
