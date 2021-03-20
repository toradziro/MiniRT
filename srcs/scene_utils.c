/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 00:05:15 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:05:17 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_scene		*ft_init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		killed_by_error(MALLOC_ERROR);
	memset(scene, 0, sizeof(t_scene));
	return (scene);
}

void		free_scene(t_scene *scene)
{
	free_cams(scene->cams);
	free_light(scene->lights);
	free_fig_test(scene->figures);
	free(scene->mlx);
	free(scene->window);
}
