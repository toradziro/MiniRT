/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:11:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/01 22:44:52 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/MiniRT.h"

void 	parser(char *str, s_scene *scene)
{
	if (str[0] == 'R')
		parse_size(str + 1, scene);
	else if (str[0] == 'A')
		parse_ambl(str + 1, scene);
	else if (str[0] == 'c')
		parse_cam(str + 1, scene);
	else if (str[0] == 'l')
		parse_light(str + 1, scene);
	else if (str[0] == 's' && str[1] == 'p')
		parse_sphere(str + 2, scene);
	else if (str[0] == 'p' && str[1] == 'l')
		parse_plane(str + 2, scene);
	else if (str[0] == 's' && str[1] == 'q')
		parse_square(str + 2, scene);
	else if (str[0] == 'c' && str[1] == 'y')
		parse_cylinder(str + 2, scene);
	else if (str[0] == 't' && str[1] == 'r')
		parse_triangle(str + 2, scene);
	else
		killed_by_error(UNKNWN_ARG);
}

char		*skip_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char		*skip_pattern(char *str)
{
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (!*str || *str != ' ')
		killed_by_error(UNKNWN_ARG);
	str = skip_spaces(str);
	return (str);
}

char		*skip_nums(char *str)
{
	if (*str && *str == '-')
		++str;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str == '.')
	{
		str++;
		while (*str && (*str >= '0' && *str <= '9'))
			str++;
	}
	return (str);
}

s_point		*parse_coordinares(char *str)
{
	float	x;
	float	y;
	float	z;
	s_point	*new;

	x = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	y = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	z = d_atoi(str);
	new = new_point(x, y, z);
	return (new);

}

void 			parse_size(char *str, s_scene *scene)
{
	str = skip_spaces(str); //add check for num
	scene->width = (int)d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	scene->height = (int)d_atoi(str);
	scene->is_size++;
}

void 			parse_ambl(char *str, s_scene *scene)
{
	s_ab_light	*new;

	if (!(new = (s_ab_light*)malloc(sizeof(s_ab_light))))
		killed_by_error(MALLOC_ERROR);
	str = skip_spaces(str);
	new->intensity = d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	new->color = col_parse(str);
	scene->ab_light = new;
	scene->is_amb_l++;
}

void 	parse_cam(char *str, s_scene *scene)
{
	s_cameras	*new;
	s_vector	*dir;
	s_point		*coor;
	float 		fov;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	dir = (s_vector*)parse_coordinares(str);
	str = skip_pattern(str);
	fov = d_atoi(str);
	new = new_camera_node(coor, dir, fov);
	if (!scene->cams)
	{
		scene->cams = new;
		scene->first_cam = scene->cams;
	}
	else
		push_back_cam(scene->cams, coor, dir, fov);
	scene->is_cam++;
}

void	 		parse_light(char *str, s_scene *scene)
{
	s_lights	*new;
	s_point		*coor;
	float		intens;
	s_color		color;

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

void 			parse_sphere(char *str, s_scene *scene)
{
	float		radius;
	s_point		*coordinates;
	s_color 	color;
	s_sphere	*new;

	str = skip_spaces(str);
	coordinates = parse_coordinares(str);
	str = skip_pattern(str);
	radius = d_atoi(str) / 2.0;
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_sphere(radius, coordinates, color);
	if (!(scene->figures))
		scene->figures = new_figur_list((void*)new, S_SP);
	else
		push_back_figur(scene->figures, (void*)new, S_SP);
}

void	 		parse_plane(char *str, s_scene *scene)
{
	s_plane		*new;
	s_point		*coor;
	s_vector	*normal;
	s_color		color;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	normal = (s_vector*)parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_plane((s_vector*)coor, normal, color);
	if (!(scene->figures))
		scene->figures = new_figur_list((void*)new, S_PL);
	else
		push_back_figur(scene->figures, (void*)new, S_PL);
}

void			parse_square(char *str, s_scene *scene)
{
	s_square	*new;
	s_point		*center;
	s_vector	*normal;
	float		size;
	s_color		color;

	str = skip_spaces(str);
	center = parse_coordinares(str);
	str = skip_pattern(str);
	normal = (s_vector*)parse_coordinares(str);
	str = skip_pattern(str);
	size = d_atoi(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_square(center, normal, size, color);
	if (!(scene->figures))
		scene->figures = new_figur_list((void*)new, S_SQ);
	else
		push_back_figur(scene->figures, (void*)new, S_SQ);
}

void			parse_cylinder(char *str, s_scene *scene)
{
	s_cylinder	*new;
	s_color		color = {0, 0, 0};

	new = new_cylinder(NULL, NULL, 0, 0, color);
	str = skip_spaces(str);
	new->coordinates = parse_coordinares(str);
	str = skip_pattern(str);
	new->normal = (s_vector*)parse_coordinares(str);
	str = skip_pattern(str);
	new->diameter = d_atoi(str);
	str = skip_pattern(str);
	new->height = d_atoi(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new->color = color;
	if (!(scene->figures))
		scene->figures = new_figur_list((void*)new, S_CL);
	else
		push_back_figur(scene->figures, (void*)new, S_CL);
}

void			parse_triangle(char *str, s_scene *scene)
{
	s_triangle	*new;
	s_color		color = {0, 0, 0};

	new = new_triangle(NULL, NULL, NULL, color);
	str = skip_spaces(str);
	new->a = parse_coordinares(str);
	str = skip_pattern(str);
	new->b = parse_coordinares(str);
	str = skip_pattern(str);
	new->c = parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new->color = color;
	new->normal = NULL;
	new->ab = subs_vectors((s_vector*)new->b, (s_vector*)new->a);
	new->ac = subs_vectors((s_vector*)new->c, (s_vector*)new->a);
	new->bc = subs_vectors((s_vector*)new->c, (s_vector*)new->b);
	new->normal = cross_prod(new->bc, new->ab);
	new->normal = vector_normalise(new->normal);
	if (!(scene->figures))
		scene->figures = new_figur_list(new, S_TR);
	else
		push_back_figur(scene->figures, new, S_TR);
}
