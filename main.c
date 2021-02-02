/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/02 22:04:36 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/MiniRT.h"

int			main(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	s_point		*sphere_center = new_point(3, 2, -100);
	s_sphere	*sphere = new_sphere(sphere_center, 50);
	s_point		*camera_center = new_point(0, 0, 0);
	s_vector	*camera_dir = new_vector(0, 0, -1);
	s_camera	*camera = new_camera(camera_dir, camera_center, 120);
	s_scene		*scene = new_scene(camera, sphere);
	scene->width = 1200;
	scene->hieght = 800;
	window = mlx_new_window(mlx, scene->width, scene->hieght, "Hello");
	ray_trace(mlx, window, scene);
	//free_scene(scene);
	mlx_loop(mlx);
	return (0);
}
