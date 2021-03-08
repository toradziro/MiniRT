/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/08 19:18:35 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/MiniRT.h"

int			main(int argc, char **argv)
{
	s_scene		*scene;
	int			fd;
	char 		*line;
	char 		*tmp;

	if (argc != 2 && argc != 3)
		killed_by_error(INV_AM_OF_ARG);
	if (argc == 2)
		check_valid_name(argv[1]);
	scene = ft_init_scene();
	if (!(scene->mlx = mlx_init()))
		killed_by_error(MALLOC_ERROR);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == '\n' || !line[0] || line[0] == '#')
		{
			free (line);
			continue ;
		}
		tmp = line;
		parser(tmp, scene);
		free(line);
	}
	//printf("start\n");
	//print_scene(scene);
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, "MiniRT");
	mlx_hook(scene->window, 2, 0, press_key, scene);
	//mlx_hook(scene->window, 17, 0, killed_by_error, 0);
	threads(scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}

int		press_key(int key, s_scene *scene)
{
	if (key == KEY_TAB)
	{
		if (scene->cams->next)
			scene->cams = scene->cams->next;
		else
			scene->cams = scene->first_cam;
	}
	else if (key == KEY_W)
		scene->cams->coordinates.v_z += 5;
	else if (key == KEY_S)
		scene->cams->coordinates.v_z -= 5;
	else if (key == KEY_A)
		scene->cams->coordinates.v_x += 5;
	else if (key == KEY_D)
		scene->cams->coordinates.v_x -= 5;
	else if (key == KEY_Q)
		scene->cams->coordinates.v_y += 5;
	else if (key == KEY_E)
		scene->cams->coordinates.v_y -= 5;
	else if (key == KEY_ESC)
		exit(0);
	threads(scene);
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
	scene->window = NULL;
	scene->mlx = NULL;
	scene->img.addr = 0;
	return (scene);
}

void		free_scene(s_scene *scene)
{
	free (scene->cams);
	free (scene->figures);
	free (scene->mlx);
	free (scene->window);
	free (scene->lights);
	free (scene);
}
