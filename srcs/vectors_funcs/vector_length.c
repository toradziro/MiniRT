/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:38 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:28 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	vector_length(t_vector v)
{
	return (sqrt(v.v_x * v.v_x + v.v_y * v.v_y + v.v_z * v.v_z));
}
