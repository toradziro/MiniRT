/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 22:31:15 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:06:25 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			parse_size(char *str, t_scene *scene)
{
	int			x;
	int			y;
	int			tmp_x;
	int			tmp_y;

	mlx_get_screen_size(scene->mlx, &x, &y);
	str = skip_spaces(str);
	tmp_x = (int)d_atoi(str);
	scene->width = MIN(tmp_x, x);
	str = skip_nums(str);
	str = skip_spaces(str);
	tmp_y = (int)d_atoi(str);
	scene->height = MIN(tmp_y, y);
	scene->is_size++;
}

void			parse_ambl(char *str, t_scene *scene)
{
	t_ab_light	*new;

	if (!(new = (t_ab_light*)malloc(sizeof(t_ab_light))))
		killed_by_error(MALLOC_ERROR);
	str = skip_spaces(str);
	new->intensity = d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	new->color = col_parse(str);
	new->color = multip_color(&new->color, new->intensity);
	scene->ab_light = new;
	scene->is_amb_l++;
}

void			parse_cam(char *str, t_scene *scene)
{
	t_cameras	*new;
	t_vector	dir;
	t_vector	coor;
	float		fov;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	dir = parse_coordinares(str);
	str = skip_pattern(str);
	fov = d_atoi(str);
	new = new_camera_node(coor, vector_normalise(dir), fov);
	if (!scene->cams)
	{
		scene->cams = new;
		scene->first_cam = scene->cams;
	}
	else
		push_back_cam(scene->cams, new);
	scene->is_cam++;
}

void			parse_light(char *str, t_scene *scene)
{
	t_lights	*new;
	t_vector	coor;
	float		intens;
	t_color		color;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	intens = d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	color = col_parse(str);
	new = new_light_node(coor, intens, color);
	if (!(scene->lights))
		scene->lights = new;
	else
		push_back_light(scene->lights, coor, intens, color);
	scene->is_light++;
}

void			parse_sphere(char *str, t_scene *scene)
{
	float		radius;
	t_vector	coordinates;
	t_color		color;
	t_sphere	*new;
	t_figures	*tmp;

	str = skip_spaces(str);
	coordinates = parse_coordinares(str);
	str = skip_pattern(str);
	radius = d_atoi(str) / 2.0;
	if (radius <= 0)
		killed_by_error(UNKNWN_ARG);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_sphere(radius, coordinates, color);
	tmp = new_figur_list((void*)new, S_SP);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}
