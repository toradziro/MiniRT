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
#include <time.h>

typedef struct s_primitives_amount
{
    i32 lights_count;
    i32 figures_count;
    i32 cams_count;
} primitives_amount;

primitives_amount calculate_primitives(str8 file, t_memory_arena* arena)
{
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
            arena_pop(arena, line.size);
        }
        if (line.mem[0] == 'c' && line.mem[1] == 'y')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 'c')
        {
            ++amount.cams_count;
        }
        else if (line.mem[0] == 'l')
        {
            ++amount.lights_count;
        }
        else if (line.mem[0] == 's' && line.mem[1] == 'p')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 'p' && line.mem[1] == 'l')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 's' && line.mem[1] == 'q')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 't' && line.mem[1] == 'r')
        {
            ++amount.figures_count;
        }
        arena_pop(arena, line.size);
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

    // preallocate_memory();
    u32 curr = 0;
    while (curr < file.size)
    {
        str8 line = get_next_line(file, &curr, arena);
        if (!line.mem[0] || line.mem[0] == '#')
        {
            continue;
        }
        parse_primitives((char*)line.mem, scene);
        arena_pop(arena, line.size);
    }

    clean_file(&file);
}

void parse_primitives(char* str, t_scene* scene)
{
    if (str[0] == 'c' && str[1] == 'y')
    {
        parse_cylinder(str + 2, scene);
    }
    else if (str[0] == 'R')
    {
        parse_size(str + 1, scene);
    }
    else if (str[0] == 'A')
    {
        parse_ambl(str + 1, scene);
    }
    else if (str[0] == 'c')
    {
        parse_cam(str + 1, scene);
    }
    else if (str[0] == 'l')
    {
        parse_light(str + 1, scene);
    }
    else if (str[0] == 's' && str[1] == 'p')
    {
        parse_sphere(str + 2, scene);
    }
    else if (str[0] == 'p' && str[1] == 'l')
    {
        parse_plane(str + 2, scene);
    }
    else if (str[0] == 's' && str[1] == 'q')
    {
        parse_square(str + 2, scene);
    }
    else if (str[0] == 't' && str[1] == 'r')
    {
        parse_triangle(str + 2, scene);
    }
    else
    {
        killed_by_error(UNKNWN_ARG);
    }
}

void parse_plane(char* str, t_scene* scene)
{
    t_plane new;
    t_vector        coor   = new_vector(0, 0, 0);
    t_vector        normal = new_vector(0, 0, 0);
    t_color         color;
    t_figure_holder tmp;

    str               = skip_spaces(str);
    coor              = parse_coordinares(str);
    str               = skip_pattern(str);
    normal            = parse_coordinares(str);
    str               = skip_pattern(str);
    color             = col_parse(str);
    new               = new_plane(coor, vector_normalise(normal), color);
    tmp.type          = Plane;
    tmp._figure.plane = new;
    scene->figures    = add_elem_vec(scene->figures, tmp);
    scene->is_figur++;
}

void parse_square(char* str, t_scene* scene)
{
    t_square new;
    t_vector        center;
    t_vector        normal;
    float           size;
    t_figure_holder tmp;

    str                = skip_spaces(str);
    center             = parse_coordinares(str);
    str                = skip_pattern(str);
    normal             = parse_coordinares(str);
    normal             = vector_normalise(normal);
    str                = skip_pattern(str);
    size               = d_atoi(str);
    str                = skip_pattern(str);
    new                = new_square(center, vector_normalise(normal), size, col_parse(str));
    tmp.type           = Square;
    tmp._figure.square = new;
    scene->figures     = add_elem_vec(scene->figures, tmp);
    scene->is_figur++;
}

void parse_cylinder(char* str, t_scene* scene)
{
    t_cylinder new;
    t_vector        tmp;
    t_vector        tmp_n;
    t_figure_holder tmp_fig;

    str                      = skip_spaces(str);
    tmp                      = parse_coordinares(str);
    str                      = skip_pattern(str);
    tmp_n                    = parse_coordinares(str);
    str                      = skip_pattern(str);
    new                      = new_cylinder(tmp, tmp_n, 0, new_color(0, 0, 0));
    new.diameter             = d_atoi(str);
    str                      = skip_pattern(str);
    new.height               = d_atoi(str);
    str                      = skip_pattern(str);
    new.color                = col_parse(str);
    tmp_fig.type             = Cylender;
    tmp_fig._figure.cylender = new;
    scene->figures           = add_elem_vec(scene->figures, tmp_fig);
    scene->is_figur++;
}

void parse_triangle(char* str, t_scene* scene)
{
    t_triangle new;
    t_vector        tmp_a;
    t_vector        tmp_b;
    t_vector        tmp_c;
    t_figure_holder tmp_fig;

    str                      = skip_spaces(str);
    tmp_a                    = parse_coordinares(str);
    str                      = skip_pattern(str);
    tmp_b                    = parse_coordinares(str);
    str                      = skip_pattern(str);
    tmp_c                    = parse_coordinares(str);
    str                      = skip_pattern(str);
    new                      = new_triangle(tmp_a, tmp_b, tmp_c, col_parse(str));
    new.normal               = new_vector(0, 0, 0);
    new.ab                   = subs_vectors(tmp_b, tmp_a);
    new.ac                   = subs_vectors(tmp_c, tmp_a);
    new.normal               = cross_prod(new.ab, new.ac);
    new.normal               = vector_normalise(new.normal);
    tmp_fig.type             = Triangle;
    tmp_fig._figure.triangle = new;
    scene->figures           = add_elem_vec(scene->figures, tmp_fig);
    scene->is_figur++;
}

void parse_sphere(char* str, t_scene* scene)
{
    float    radius;
    t_vector coordinates;
    t_color  color;
    t_sphere new;
    t_figure_holder tmp;

    str         = skip_spaces(str);
    coordinates = parse_coordinares(str);
    str         = skip_pattern(str);
    radius      = d_atoi(str) / 2.0;
    if (radius <= 0)
    {
        killed_by_error(UNKNWN_ARG);
    }
    str                = skip_pattern(str);
    color              = col_parse(str);
    new                = new_sphere(radius, coordinates, color);
    tmp._figure.sphere = new;
    tmp.type           = Sphere;
    scene->figures     = add_elem_vec(scene->figures, tmp);
    scene->is_figur++;
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
    scene->is_size++;
}

void parse_ambl(char* str, t_scene* scene)
{
    t_ab_light* new;

    if (!(new = (t_ab_light*)malloc(sizeof(t_ab_light))))
    {
        killed_by_error(MALLOC_ERROR);
    }
    str             = skip_spaces(str);
    new->intensity  = d_atoi(str);
    str             = skip_nums(str);
    str             = skip_spaces(str);
    new->color      = col_parse(str);
    new->color      = multip_color(&new->color, new->intensity);
    scene->ab_light = new;
    scene->is_amb_l++;
}

void parse_cam(char* str, t_scene* scene)
{
    t_cameras* new;
    t_vector dir;
    t_vector coor;
    float    fov;

    str  = skip_spaces(str);
    coor = parse_coordinares(str);
    str  = skip_pattern(str);
    dir  = parse_coordinares(str);
    str  = skip_pattern(str);
    fov  = d_atoi(str);
    new  = new_camera_node(coor, vector_normalise(dir), fov);
    if (!scene->cams)
    {
        scene->cams      = new;
        scene->first_cam = scene->cams;
    }
    else
    {
        push_back_cam(scene->cams, new);
    }
    scene->is_cam++;
}

void parse_light(char* str, t_scene* scene)
{
    t_lights* new;
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
    new    = new_light_node(coor, intens, color);
    if (!(scene->lights))
    {
        scene->lights = new;
    }
    else
    {
        push_back_light(scene->lights, coor, intens, color);
    }
    scene->is_light++;
}
