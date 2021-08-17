/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lights_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:29:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:30:38 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_lights		*new_light_node(t_vector coordinates,
				float intensity, t_color color)
{
	t_lights	*new;
	t_vector	tmp;

	tmp = new_vector(0, 0, 0);
	if (!(new = (t_lights*)malloc(sizeof(t_lights))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->intensity = intensity;
	new->color = color;
	new->light_dir = tmp;
	new->next = NULL;
	return (new);
}

void			push_back_light(t_lights *list,
				t_vector coordinates, float intensity, t_color color)
{
	t_lights	*tmp;

	tmp = new_light_node(coordinates, intensity, color);
	while (list->next)
		list = list->next;
	list->next = tmp;
}
