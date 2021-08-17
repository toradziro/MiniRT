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

#include "../includes/MiniRT.h"

void			parser(char *str, t_scene *scene)
{
	if (str[0] == 'c' && str[1] == 'y')
		parse_cylinder(str + 2, scene);
	else if (str[0] == 'R')
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
	else if (str[0] == 't' && str[1] == 'r')
		parse_triangle(str + 2, scene);
	else
		killed_by_error(UNKNWN_ARG);
}

void			parse_plane(char *str, t_scene *scene)
{
	t_plane		*new;
	t_vector	coor;
	t_vector	normal;
	t_color		color;
	t_figures	*tmp;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	normal = parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_plane(coor, vector_normalise(normal), color);
	tmp = new_figur_list((void*)new, S_PL);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}

void			parse_square(char *str, t_scene *scene)
{
	t_square	*new;
	t_vector	center;
	t_vector	normal;
	float		size;
	t_figures	*tmp;

	str = skip_spaces(str);
	center = parse_coordinares(str);
	str = skip_pattern(str);
	normal = parse_coordinares(str);
	normal = vector_normalise(normal);
	str = skip_pattern(str);
	size = d_atoi(str);
	str = skip_pattern(str);
	new = new_square(center, vector_normalise(normal), size, col_parse(str));
	tmp = new_figur_list((void*)new, S_SQ);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}

void			parse_cylinder(char *str, t_scene *scene)
{
	t_cylinder	*new;
	t_vector	tmp;
	t_vector	tmp_n;
	t_figures	*tmp_fig;

	str = skip_spaces(str);
	tmp = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_n = parse_coordinares(str);
	str = skip_pattern(str);
	new = new_cylinder(tmp, tmp_n, 0, new_color(0, 0, 0));
	new->diameter = d_atoi(str);
	str = skip_pattern(str);
	new->height = d_atoi(str);
	str = skip_pattern(str);
	new->color = col_parse(str);
	tmp_fig = new_figur_list((void*)new, S_CL);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp_fig);
	scene->is_figur++;
	free(tmp_fig);
}

void			parse_triangle(char *str, t_scene *scene)
{
	t_triangle	*new;
	t_vector	tmp_a;
	t_vector	tmp_b;
	t_vector	tmp_c;
	t_figures	*tmp_fig;

	str = skip_spaces(str);
	tmp_a = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_b = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_c = parse_coordinares(str);
	str = skip_pattern(str);
	new = new_triangle(tmp_a, tmp_b, tmp_c, col_parse(str));
	new->normal = new_vector(0, 0, 0);
	new->ab = subs_vectors(tmp_b, tmp_a);
	new->ac = subs_vectors(tmp_c, tmp_a);
	new->normal = cross_prod(new->ab, new->ac);
	new->normal = vector_normalise(new->normal);
	tmp_fig = new_figur_list((void*)new, S_TR);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp_fig);
	scene->is_figur++;
	free(tmp_fig);
}
