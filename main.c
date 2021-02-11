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
//void 	print_scene(s_scene *scene);
//void 	print_color(s_color c);
//void    print_point(s_point *p);

int			main(void)
{
	s_scene		*scene;
	int			fd;
	char 		*line;
	char 		*tmp;

//	if (argc != 2 && argc != 3)
//		killed_by_error(INV_AM_OF_ARG);
//	if (argc == 2)
//		check_valid_name(argv[1]);
	scene = ft_init_scene();
	fd = open("minirt.rt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tmp = line;
		printf ("line = %s\n", line);
		parser(tmp, scene);
		free(line);
	}
	printf("???\n");
	parser(line, scene);
//	free(line);
//	print_scene(scene);
	return (0);
}

s_scene		*ft_init_scene(void)
{
	s_scene	*scene;

	if (!(scene = (s_scene*)malloc(sizeof(s_scene))))
		killed_by_error(MALLOC_ERROR);
	scene->height = 0;
	scene->width = 0;
	scene->cams = NULL;
	scene->figures = NULL;
	scene->lights = NULL;
	scene->ab_light = NULL;
	scene->is_amb_l = 0;
	scene->is_cam = 0;
	scene->is_figur = 0;
	scene->is_light = 0;
	scene->is_size = 0;
	return (scene);
}
/*
* "+R 100 | 100" - x, y are size of render
* "+A 0.2 | 255,255,255" - ambient light, 0,2 is intensity, other is color
* "c 50.0, 0, 20.0  |  0,1,0 | 70" - camera x,y,z are view point, 3d normalized vector, field of view
* "l -40.0,50.0,0.0 | 0.6 |  10,0,255" - light x,y,z are coordinates of light point, intensity, color
* "sp 0.0,0.0,20.0 |  12.6 |  10,0,255" - coordinates, diameter, color
* "pl 0.0,1.0,2.0  |  1.0,0.0,0.0 | 255,0,255" - coordinates, 3d normalized vector, color
* "sq 0.0,0.0,20.6 | 1.0,0.0,0.0 | 12.6 | 255,0,255" - coordinates of center square, 3d norm vector, side size, color
* "cy 50.0,0.0,20.6 | 0.0,0.0,1.0 | 10,0,255 | 14.2 | 21.42" - xyz coor | 3d norm vector | cylinder diameter | height | color
* "tr 10.0,20.0,10.0 | 10.0,10.0,20.0 | 20.0,10.0,10.0 | 0,0,255" - xyz first point | xyz s_point | xyz th_point | color
*/
//void 	print_scene(s_scene *scene)
//{
//	printf("---------R----------\n");
//	printf("%f | %f\n\n", scene->width, scene->height);
//	printf("---------A----------\n");
//	printf("intensity: %f\n", scene->ab_light->intensity);
//	printf("color: ");
//	print_color(scene->ab_light->color);
//	printf("\n\n");
//	printf("---------c----------\n");
//}
//
//void 	print_color(s_color c)
//{
//	printf("%i, %i, %i", c.r, c.g, c.b);
//}
//
//void    print_point(s_point *p)
//{
//	printf("%f, %f, %f", p->p_x, p->p_y, p->p_z);
//}