#include "color.h"

t_color multip_color(t_color* color, float coeff)
{
    t_color res;

    res.r = coeff * color->r;
    if (res.r >= 255)
    {
        res.r = 255;
    }
    res.g = coeff * color->g;
    if (res.g >= 255)
    {
        res.g = 255;
    }
    res.b = coeff * color->b;
    if (res.b >= 255)
    {
        res.b = 255;
    }
    return (res);
}

t_color add_color(t_color* color, t_color* color_s)
{
    color->r = color->r + color_s->r;
    if (color->r >= 255)
    {
        color->r = 255;
    }
    color->g = color->g + color_s->g;
    if (color->g >= 255)
    {
        color->g = 255;
    }
    color->b = color->b + color_s->b;
    if (color->b >= 255)
    {
        color->b = 255;
    }
    return (*color);
}
