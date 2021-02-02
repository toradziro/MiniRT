#include "../includes/MiniRT.h"

int			sphere_intersect(s_camera *camera, s_vector *ray, s_sphere *sp)
{
	double		b;
	double		c;
	double		discr;
	double		x_one;
	double		x_two;
	s_vector	*res;

	x_one = 0;
	x_two = 0;
	res = subs_vectors((s_vector*)camera->coordinates, (s_vector*)sp->coordinates);
	b = 2 * vector_scalar_mult(res, ray);
	c = vector_scalar_mult(res, res) - (sp->radius * sp->radius);
	discr = (b * b) - (4 * c);
	free(res);
	if (discr < 0)
		return (0);
	x_one = (-b - sqrt(discr)) / 2;
	x_two = (-b + sqrt(discr)) / 2;
	if (x_one > 0)
		return (1);
	return (0);
}
