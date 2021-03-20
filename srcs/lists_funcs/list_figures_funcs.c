/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_figures_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:28:49 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:29:54 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_figures		*new_figur_list(void *content, char spec)
{
	t_figures	*new;

	if (!(new = (t_figures*)malloc(sizeof(t_figures))))
		killed_by_error(MALLOC_ERROR);
	new->content = content;
	new->specif = spec;
	return (new);
}
