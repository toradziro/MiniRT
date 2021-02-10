#include "../includes/MiniRT.h"

s_sphere		*new_sphere(double radius, s_point *coordinates, s_color color)
{
	s_sphere	*new;

	if (!(new = (s_sphere*)malloc(sizeof(s_sphere))))
		killed_by_error(MALLOC_ERROR);
	new->radius = radius;
	new->coordinates = coordinates;
	new->color = color;
	return (new);
}

s_plane			*new_plane(s_vector *coordinates, s_vector *normal, s_color color)
{
	s_plane		*new;

	if (!(new = (s_plane *)malloc(sizeof(s_plane))))
		killed_by_error(MALLOC_ERROR);
	new->normal = normal;
	new->coordinates = coordinates;
	new->color = color;
	return (new);
}

s_square		*new_square(s_point *center, s_vector *normal, double side, s_color color)
{
	s_square	*new;

	if (!(new = (s_square*)malloc(sizeof(s_square))))
		killed_by_error(MALLOC_ERROR);
	new->center = center;
	new->normal = normal;
	new->color = color;
	new->side = side;
	return (new);
}

s_cylinder		*new_cylinder(s_point *coordinates, s_vector *normal, double diameter, double height, s_color *color)
{
	s_cylinder	*new;

	if (!(new = (s_cylinder*)malloc(sizeof(s_cylinder))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->normal = normal;
	new->diameter = diameter;
	new->height = height;
	new->color = color;
	return (new);
}

s_triangle		*new_triangle(s_point *frs_point, s_point *sec_point, s_point *thd_point, s_color *color)
{
	s_triangle	*new;

	if (!(new = (s_triangle*)malloc(sizeof(s_triangle))))
		killed_by_error(MALLOC_ERROR);
	new->frs_point = frs_point;
	new->sec_point = sec_point;
	new->thd_point = thd_point;
	new->color = color;
	return (new);
}