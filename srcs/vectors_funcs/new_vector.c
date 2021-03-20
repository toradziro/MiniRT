/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:15 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:22 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector		new_vector(float x, float y, float z)
{
	t_vector	new;

	new.v_x = x;
	new.v_y = y;
	new.v_z = z;
	return (new);
}
