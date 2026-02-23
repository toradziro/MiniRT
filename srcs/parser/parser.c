/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:11:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:25:14 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../file/rt_file.h"
#include "../includes/MiniRT.h"
#include "../string/rt_string.h"

typedef struct s_primitives_amount
{
    i32 lights_count;
    i32 figures_count;
    i32 cams_count;
} primitives_amount;

primitives_amount calculate_primitives(str8 file, t_memory_arena* arena)
{
    // TODO: Remove allocations in strings
    primitives_amount amount;
    amount.figures_count = 0;
    amount.cams_count    = 0;
    amount.lights_count  = 0;

    u32 curr = 0;
    while (curr < file.size)
    {
        str8 line = get_next_line(file, &curr, arena);
        if (!line.mem[0] || line.mem[0] == '#')
        {
            continue;
        }
        else if (line.mem[0] == 'c')
        {
            ++amount.cams_count;
        }
        else if (line.mem[0] == 'l')
        {
            ++amount.lights_count;
        }
        else if (line.mem[0] == 't' && line.mem[1] == 'r')
        {
            ++amount.figures_count;
        }
    }
    return amount;
}

void start_parse(t_scene* scene, const char* path, t_memory_arena* arena)
{
    str8 file;

    //-- Read full file
    file                     = read_full_file(path);
    primitives_amount amount = calculate_primitives(file, arena);
    scene->figures           = new_vec_fig(amount.figures_count, arena);

    u32 curr = 0;
    while (curr < file.size)
    {
        str8 line = get_next_line(file, &curr, arena);
        if (line.mem[0] == '#')
        {
            continue;
        }
        parse_primitives((char*)line.mem, scene, arena);
    }

    clean_file(&file);
}

void parse_primitives(char* str, t_scene* scene, t_memory_arena* arena)
{
    if (str[0] == 'R')
    {
        parse_size(str + 1, scene);
    }
    else if (str[0] == 'A')
    {
        parse_ambl(str + 1, scene, arena);
    }
    else if (str[0] == 'c')
    {
        parse_cam(str + 1, scene, arena);
    }
    else if (str[0] == 'l')
    {
        parse_light(str + 1, scene, arena);
    }
    else if (str[0] == 't' && str[1] == 'r')
    {
        parse_triangle(str + 2, scene);
    }
}

void parse_triangle(char* str, t_scene* scene)
{
    t_triangle new       = {0};
    new.reflection_value = 0;
    t_vector tmp_a;
    t_vector tmp_b;
    t_vector tmp_c;

    str   = skip_spaces(str);
    tmp_a = parse_coordinares(str);
    str   = skip_pattern(str);
    tmp_b = parse_coordinares(str);
    str   = skip_pattern(str);
    tmp_c = parse_coordinares(str);
    str   = skip_pattern(str);
    new   = new_triangle(tmp_a, tmp_b, tmp_c, col_parse(str));
    str   = skip_pattern(str);
    if (*str)
    {
        new.reflection_value = d_atoi(str);
    }
    new.normal     = new_vector(0, 0, 0);
    new.ab         = subs_vectors(&tmp_b, &tmp_a);
    new.ac         = subs_vectors(&tmp_c, &tmp_a);
    new.normal     = cross_prod(&new.ab, &new.ac);
    new.normal     = vector_normalize(&new.normal);
    scene->figures = add_elem_vec(scene->figures, new);
}

void parse_size(char* str, t_scene* scene)
{
    int x;
    int y;
    int tmp_x;
    int tmp_y;

    x             = 2560;
    y             = 1800;
    str           = skip_spaces(str);
    tmp_x         = (int)d_atoi(str);
    scene->width  = MIN(tmp_x, x);
    str           = skip_nums(str);
    str           = skip_spaces(str);
    tmp_y         = (int)d_atoi(str);
    scene->height = MIN(tmp_y, y);
}

void parse_ambl(char* str, t_scene* scene, t_memory_arena* arena)
{
    t_ab_light* new = arena_push(arena, sizeof(t_ab_light));
    str             = skip_spaces(str);
    new->intensity  = d_atoi(str);
    str             = skip_nums(str);
    str             = skip_spaces(str);
    new->color      = col_parse(str);
    new->color      = multip_color(&new->color, new->intensity);
    scene->ab_light = new;
}

void parse_cam(char* str, t_scene* scene, t_memory_arena* arena)
{
    t_cameras* new = NULL;
    t_vector dir;
    t_vector coor;
    float    fov;

    str  = skip_spaces(str);
    coor = parse_coordinares(str);
    str  = skip_pattern(str);
    dir  = parse_coordinares(str);
    str  = skip_pattern(str);
    fov  = d_atoi(str);
    new  = new_camera_node(coor, vector_normalize(&dir), fov, arena);
    if (!scene->cams)
    {
        scene->cams      = new;
        scene->first_cam = scene->cams;
    }
    else
    {
        push_back_cam(scene->cams, new);
    }
}

void parse_light(char* str, t_scene* scene, t_memory_arena* arena)
{
    t_lights* new = NULL;
    t_vector coor;
    float    intens;
    t_color  color;

    str    = skip_spaces(str);
    coor   = parse_coordinares(str);
    str    = skip_pattern(str);
    intens = d_atoi(str);
    str    = skip_nums(str);
    str    = skip_spaces(str);
    color  = col_parse(str);
    new    = new_light_node(coor, intens, color, arena);
    if (!(scene->lights))
    {
        scene->lights = new;
    }
    else
    {
        push_back_light(scene->lights, coor, intens, color, arena);
    }
}
