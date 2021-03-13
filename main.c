/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/11 21:07:47 by ehillman         ###   ########.fr       */
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
	check_scene(scene);
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, "MiniRT");
	mlx_hook(scene->window, 2, 0, press_key, scene);
	mlx_hook(scene->window, 17, 0, exit_rt, scene);
	if (argc == 3 && !strcmp(argv[2], "--save"))
		scene->is_save = 1;
	threads(scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}

int 	exit_rt(s_scene *scene)
{
	free_scene(scene);
	exit(0);
	return (0);
}

void	check_scene(s_scene *scene)
{
	if (!scene->is_amb_l || !scene->is_cam || !scene->is_figur || !scene->is_light || !scene->is_size)
		killed_by_error(NOT_ENOUGH);
}

int		press_key(int key, s_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
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
	{
		free_scene(scene);
		exit(0);
	}
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
	scene->is_save = 0;
	scene->window = NULL;
	scene->mlx = NULL;
	scene->img.addr = 0;
	return (scene);
}

void		free_scene(s_scene *scene)
{
	free_cams(scene->cams);
	free_light (scene->lights);
	free_fig_test (scene->figures);
	free (scene->mlx);
	free (scene->window);
	free (scene);
}

void			free_fig_test(s_vec_fig *v)
{
	int			i;
	int			len;

	i = 0;
	len = v->length;
	while (i < len)
	{
		if (v->node[i].specif == S_SP)
			free((s_sphere*)v->node[i].content);
		else if (v->node[i].specif == S_PL)
			free((s_plane*)v->node[i].content);
		else if (v->node[i].specif == S_SQ)
			free((s_square*)v->node[i].content);
		else if (v->node[i].specif == S_TR)
			free((s_triangle*)v->node[i].content);
		else if (v->node[i].specif == S_CL)
			free((s_cylinder*)v->node[i].content);
		++i;
	}
	free (v->node);
	free (v);
}

void		free_cams(s_cameras *cam)
{
	s_cameras	*tmp;

	while (cam)
	{
		tmp = cam->next;
		free (cam);
		cam = tmp;
	}
}

void		free_light(s_lights *light)
{
	s_lights	*tmp;

	while (light)
	{
		tmp = light->next;
		free (light);
		light = tmp;
	}
}
