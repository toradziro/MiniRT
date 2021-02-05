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

int			main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		killed_by_error(-2);
	if (argc == 2)
		check_valid_name(argv[1]);
	s_scene *scene;
	return (0);
}

//	void	*mlx;
//	void	*window;
//
//	mlx = mlx_init();
//	s_point		*sphere_center = new_point(10, 10, -100);
//	s_sphere	*sphere = new_sphere(sphere_center, 20);
//	s_point		*camera_center = new_point(0, 0, 0);
//	s_vector	*camera_dir = new_vector(0, 0, -1);
//	s_camera	*camera = new_camera(camera_dir, camera_center, 90);
//	s_scene		*scene = new_scene(camera, sphere);
//
//	scene->width = 1200;
//	scene->hieght = 800;
//	window = mlx_new_window(mlx, scene->width, scene->hieght, "Hello");
//	ray_trace(mlx, window, scene);
//	//free_scene(scene);
//	mlx_loop(mlx);