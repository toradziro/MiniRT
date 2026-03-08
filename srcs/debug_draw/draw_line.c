#include "draw_line.h"

void swap_i(i32* a, i32* b)
{
    i32 tmp = *a;
    *a      = *b;
    *b      = tmp;
}

bool check_fit_on_screen(i32 x, i32 y, i32 width, i32 height) { return x >= 0 && y >= 0 && x < width && y < height; }

void draw_line(iv2 a, iv2 b, void* pixels, t_color color, i32 width, i32 height)
{
    if (a.x == b.x && a.y == b.y)
    {
        if (check_fit_on_screen(a.x, a.y, width, height))
        {
            set_color(pixels, &color, a.x, a.y, width);
        }
        return;
    }
    bool swapped = false;
    if (abs(a.x - b.x) < abs(a.y - b.y))
    {
        swap_i(&a.x, &a.y);
        swap_i(&b.x, &b.y);
        swapped = true;
    }
    if (a.x > b.x)
    {
        swap_i(&a.x, &b.x);
        swap_i(&a.y, &b.y);
    }
    if (swapped)
    {
        for (i32 x = a.x; x <= b.x; ++x)
        {
            const float t = (float)(x - a.x) / (float)(b.x - a.x);
            const i32   y = round(a.y + t * (b.y - a.y));
            if (check_fit_on_screen(y, x, width, height))
            {
                set_color(pixels, &color, y, x, width);
            }
        }
    }
    else
    {
        for (i32 x = a.x; x <= b.x; ++x)
        {
            const float t = (float)(x - a.x) / (float)(b.x - a.x);
            const i32   y = round(a.y + t * (b.y - a.y));
            if (check_fit_on_screen(x, y, width, height))
            {
                set_color(pixels, &color, x, y, width);
            }
        }
    }
}
