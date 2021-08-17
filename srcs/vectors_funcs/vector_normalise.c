/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:49 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:32 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_vector		vector_normalise(t_vector v)
{
	float		len;
	float		len_coeff;
	t_vector	n;

	n = new_vector(0, 0, 0);
	len = sqrt(v.v_x * v.v_x + v.v_y * v.v_y + v.v_z * v.v_z);
	len_coeff = 1 / len;
	n.v_x = v.v_x * len_coeff;
	n.v_y = v.v_y * len_coeff;
	n.v_z = v.v_z * len_coeff;
	return (n);
}
