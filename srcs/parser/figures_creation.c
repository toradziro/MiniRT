/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:31:18 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:24:45 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere		*new_sphere(float radius, t_vector coordinates, t_color color)
{
	t_sphere	*new;

	if (!(new = (t_sphere*)malloc(sizeof(t_sphere))))
		killed_by_error(MALLOC_ERROR);
	new->radius = radius;
	new->coordinates = coordinates;
	new->color = color;
	return (new);
}

t_plane			*new_plane(t_vector coordinates, t_vector normal, t_color color)
{
	t_plane		*new;

	if (!(new = (t_plane *)malloc(sizeof(t_plane))))
		killed_by_error(MALLOC_ERROR);
	new->normal = normal;
	new->coordinates = coordinates;
	new->color = color;
	return (new);
}

t_square		*new_square(t_vector center, t_vector normal,
				float side, t_color color)
{
	t_square	*new;

	if (!(new = (t_square*)malloc(sizeof(t_square))))
		killed_by_error(MALLOC_ERROR);
	new->center = center;
	new->normal = normal;
	new->color = color;
	new->side = side;
	return (new);
}

t_cylinder		*new_cylinder(t_vector coordinates, t_vector normal,
				float diameter, t_color color)
{
	t_cylinder	*new;

	if (!(new = (t_cylinder*)malloc(sizeof(t_cylinder))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->axis = normal;
	new->diameter = diameter;
	new->height = 0;
	new->color = color;
	new->normal = new_vector(0, 0, 0);
	return (new);
}

t_triangle		*new_triangle(t_vector frt_vector, t_vector sec_point,
				t_vector thd_point, t_color color)
{
	t_triangle	*new;
	t_vector	tmp;

	tmp = new_vector(0, 0, 0);
	if (!(new = (t_triangle*)malloc(sizeof(t_triangle))))
		killed_by_error(MALLOC_ERROR);
	new->a = frt_vector;
	new->b = sec_point;
	new->c = thd_point;
	new->ab = tmp;
	new->ac = tmp;
	new->normal = tmp;
	new->color = color;
	return (new);
}
