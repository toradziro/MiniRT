/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/02 22:01:15 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"


void	ray_trace(void *mlx, void *window, s_scene *scene)
{
	int			mlx_x = 0;
	int			mlx_y = 0;
	double		win_x = -scene->width / 2;
	double		win_y = scene->hieght / 2;
	int			color;
	double		y_ray; // make struct later
	double		x_ray;
	s_vector	*ray;
	s_vplane	*vplane;
	t_vector	light_dir = new_vector(0.2, 0.3, 0.5); // in parser
	vplane = get_view_plane(scene->width, scene->hieght, scene->cams->field_of_v);
	while (win_y >= -scene->hieght / 2)
	{
		y_ray = win_y * vplane->y_pixel;
		win_x = -scene->width / 2;
		mlx_x = 0;
		while (win_x <= scene->width / 2)
		{
			x_ray = win_x * vplane->x_pixel;
			ray = new_vector(x_ray, y_ray, -1);
			ray = vector_normalise(ray, vector_length(ray));
			if (sphere_intersect(scene->cams, ray, scene->sphere))
				color = 16777215;
			

			t_point *lie_on_sphere = (t_point*)vector_by_scalar(ray, x_one);
			//t_vector normal  = lie_on_sphere - sp_center;
			//double coeff = normal * light_dir;
			//color = (цвет сфера + (col_ambient * intens) + (цвет света * coeff));
			//
			//
			else
				color = 0;
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, color);
			free(ray);
			win_x++;
			mlx_x++;
		}
		win_y--;
		mlx_y++;
	}
}

s_vplane		*get_view_plane(double width, double hieght, double fov)
{
	s_vplane	*vplane;
	double		aspect_ratio; //mashtab!

	if (!(vplane = (s_vplane*)malloc(sizeof(s_vplane))))
		killed_by_error(-1);
	aspect_ratio = width / hieght;
	vplane->width = (tan(fov / 2 * (M_PI / 180))) * 2;
	vplane->hieght = vplane->width / aspect_ratio;
	vplane->x_pixel = vplane->width / width;
	vplane->y_pixel = vplane->hieght / hieght;
	return (vplane);
}
