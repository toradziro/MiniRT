/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/13 19:47:33 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/MiniRT.h"
//void 	print_scene(s_scene *scene);
//void 	print_color(s_color c);
//void    print_point(s_point *p);

int			main(void)
{
	void		*mlx;
	void		*window;
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
		if (line[0] == '\n' || !line[0])
		{
			free (line);
			continue ;
		}
		tmp = line;
		parser(tmp, scene);
		free(line);
	}

//	s_sphere *r = (s_sphere*)scene->figures->content;
//	printf("%f, %f, %f, %f, %d, %d, %d\n", r->coordinates->p_x, r->coordinates->p_y, r->coordinates->p_z, r->radius, r->color.r, r->color.g, r->color.b);

//	printf("%d, %d\n", scene->height, scene->width);

//	printf("%f, %d, %d, %d", scene->ab_light->intensity, scene->ab_light->color.r, scene->ab_light->color.g, scene->ab_light->color.b);

// s_cameras *r = (s_cameras*)scene->cams;
// printf("%f\n", r->coordinates->p_x);
// printf("%f, %f, %f, %f, %f, %f, %f\n", r->coordinates->p_x, r->coordinates->p_y, r->coordinates->p_z, r->direction->v_x, r->direction->v_y, r->direction->v_z, r->field_of_v);


	write (1, "here\n", 5);
	mlx = mlx_init();
	window = mlx_new_window(mlx, scene->width, scene->height, "my_little_heart_attack");
//	ray_trace(mlx, window, scene);
	mlx_loop(mlx);
	return (0);
}

s_scene		*ft_init_scene(void)
{
	s_scene	*scene;

	if (!(scene = (s_scene*)malloc(sizeof(s_scene))))
		killed_by_error(MALLOC_ERROR);
	scene->height = 0;
	scene->width = 0;
	scene->cams = 0;
	scene->figures = 0;
	scene->lights = 0;
	scene->ab_light = 0;
	scene->is_amb_l = 0;
	scene->is_cam = 0;
	scene->is_figur = 0;
	scene->is_light = 0;
	scene->is_size = 0;
	return (scene);
}
