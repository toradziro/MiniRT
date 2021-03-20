/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:06:18 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int				main(int argc, char **argv)
{
	t_scene		*scene;
	int			fd;

	if (argc != 2 && argc != 3)
		killed_by_error(INV_AM_OF_ARG);
	check_valid_name(argv[1]);
	scene = ft_init_scene();
	if (!(scene->mlx = mlx_init()))
		killed_by_error(MALLOC_ERROR);
	fd = open(argv[1], O_RDONLY);
	start_parse(scene, fd);
	check_scene(scene);
	scene->window = mlx_new_window(scene->mlx,
	scene->width, scene->height, "MiniRT");
	if (argc == 3 && !strcmp(argv[2], "--save"))
		scene->is_save = 1;
	else if (argc == 3 && strcmp(argv[2], "--save"))
		killed_by_error(UNKNWN_ARG);
	mlx_hook(scene->window, 2, 0, press_key, scene);
	mlx_hook(scene->window, 17, 0, exit_rt, scene);
	mlx_hook(scene->window, 4, 0, mouse_press, scene);
	threads(scene);
	mlx_loop(scene->mlx);
	return (0);
}

void			start_parse(t_scene *scene, int fd)
{
	char		*line;
	char		*tmp;

	while (get_next_line(fd, &line))
	{
		if (!line[0] || line[0] == '#')
		{
			free(line);
			continue ;
		}
		tmp = line;
		parser(tmp, scene);
		free(line);
	}
}

int				exit_rt(t_scene *scene)
{
	free_scene(scene);
	exit(0);
	return (0);
}

void			check_scene(t_scene *scene)
{
	if (!scene->is_amb_l || !scene->is_cam ||
		!scene->is_figur || !scene->is_light || !scene->is_size)
		killed_by_error(NOT_ENOUGH);
}
