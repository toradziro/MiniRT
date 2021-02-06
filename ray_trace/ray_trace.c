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

typedef struct s_color {
	double r;
	double g;
	double b;
}				t_color;

void	multip_color(t_color *color, double coeff)
{
	color->r *= coeff;
	if (color->r >= 255)
		color->r = 255;
	color->g *= coeff;
	if (color->g >= 255)
		color->g = 255;
	color->b *= coeff;
	if (color->b >= 255)
		color->b = 255;
}

t_color	add_color(t_color color, t_color color_2)
{
	color.r = color.r + color_2.r;
	if (color.r >= 255)
		color.r = 255;
	color.g = color.g + color_2.g;
	if (color.g >= 255)
		color.g = 255;
	color.b = color.b + color_2.b;
	if (color.b >= 255)
		color.b = 255;
	return (color);
}

void	ray_trace(void *mlx, void *window, s_scene *scene)
{
	int			mlx_x = 0;
	int			mlx_y = 0;
	double		win_x;
	double		win_y = scene->hieght / 2;
	double		y_ray; // make struct later
	double		x_ray;
	s_vector	*ray;
	s_vplane	*vplane;
	s_vector	*light_dir = new_vector(400,400,200); // in parser
	int 		color;

	t_color ambient;
	ambient.r = 255;
	ambient.g = 255;
	ambient.b = 0;
	t_color res_color;
	res_color.r = 0;
	res_color.g = 70;
	res_color.b = 0;
	t_color light;
	light.r = 255;
	light.g = 255;
	light.b = 0;
	int i = 0;

	vplane = get_view_plane(scene->width, scene->height, scene->cams->field_of_v);
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
			double x_one = sphere_intersect(scene->cams, ray, scene->sphere);

			if (x_one > 0)
			{
				t_color new_c = res_color;
				t_color new_a = ambient;
				t_color new_l = light;

                s_point *lie_on_sphere = (s_point *)vector_by_scalar(ray, x_one);
                s_vector *normal = subs_vectors(((s_vector*)scene->sphere->coordinates), (s_vector*)lie_on_sphere);
                double coeff = vector_scalar_mult(vector_normalise(normal, vector_length(normal)), vector_normalise(light_dir, vector_length(light_dir))) * -1;
				//printf("%f\n", coeff);
				if (coeff < 0)
					coeff = 0;

                multip_color(&new_a, 0.1);
                multip_color(&new_l, coeff);
                new_c = add_color(new_c, add_color(new_l, new_a));
                //multip_color(&new_c, 0.5);
                color = (int)new_c.r << 16 | (int)new_c.g << 8 | (int)new_c.b;
                //i++;
			}
			else
				color = 0;
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, color);
			free(ray);
			win_x++;
			mlx_x++;
			//if (i == 50)
			//	break;
		}
		win_y--;
		mlx_y++;
	}
}

s_vplane		*get_view_plane(double width, double height, double fov)
{
	s_vplane	*vplane;
	double		aspect_ratio; //mashtab!

	if (!(vplane = (s_vplane*)malloc(sizeof(s_vplane))))
		killed_by_error(MALLOC_ERROR);
	aspect_ratio = width / height;
	vplane->width = (tan(fov / 2 * (M_PI / 180))) * 2;
	vplane->hieght = vplane->width / aspect_ratio;
	vplane->x_pixel = vplane->width / width;
	vplane->y_pixel = vplane->hieght / height;
	return (vplane);
}
