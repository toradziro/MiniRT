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
	float		len_coeff;

	len_coeff = 1 / vector_length(v);
	return vector_by_scalar(v, len_coeff);
}
