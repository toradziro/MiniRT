/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:11:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/27 00:15:55 by ehillman         ###   ########.fr       */
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
	str = skip_nums(str);
	if (*str == ',')
		str++;
	str = skip_nums(str);
	if (!*str)
		killed_by_error(UNKNWN_ARG);
	if (*str != ' ')
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
	double	x;
	double	y;
	double	z;
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
}

void 	parse_cam(char *str, s_scene *scene)
{
	s_cameras	*new;
	s_vector	*dir;
	s_point		*coor;
	double 		fov;

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
}

void	 		parse_light(char *str, s_scene *scene)
{
	s_lights	*new;
	s_point		*coor;
	double		intens;
	s_color		color;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	//print_vector((s_vector*)coor);
	str = skip_pattern(str);
	intens = d_atoi(str);
	//printf("%f\n", intens);
	str = skip_nums(str);
	str = skip_spaces(str);
	color = col_parse(str);
	//print_color(color);
	//printf("\n\n\n");
	new = new_light_node(coor, intens, color);
	if (!(scene->lights))
		scene->lights = new;
	else
		push_back_light(scene->lights, coor, intens, color);
	//print_scene(scene);
}

void 			parse_sphere(char *str, s_scene *scene)
{
	double		radius;
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
	double		size;
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
	s_color		color;

	new = new_cylinder(NULL, NULL, 0, 0, NULL);
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
	new->color = &color;
	if (!(scene->figures))
		scene->figures = new_figur_list((void*)new, S_CL);
	else
		push_back_figur(scene->figures, (void*)new, S_CL);
}

void			parse_triangle(char *str, s_scene *scene)
{
	s_triangle	*new;
	s_color		color;

	new = new_triangle(NULL, NULL, NULL, NULL);
	str = skip_spaces(str);
	new->frs_point = parse_coordinares(str);
	str = skip_pattern(str);
	new->sec_point = parse_coordinares(str);
	str = skip_pattern(str);
	new->thd_point = parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new->color = &color;
	if (!(scene->figures))
		scene->figures = new_figur_list(new, S_TR);
	else
		push_back_figur(scene->figures, new, S_TR);
}
