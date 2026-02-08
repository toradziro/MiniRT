/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_prod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:07 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:14 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_vector		cross_prod(t_vector b, t_vector a)
{
#ifdef VECTORIZE
    __m128 va1 = _mm_setr_ps(a.v_y, a.v_z, a.v_x, 0.0f);
    __m128 vb1 = _mm_setr_ps(b.v_z, b.v_x, b.v_y, 0.0f);
    __m128 vres1 = _mm_mul_ps(va1, vb1);

    __m128 va2 = _mm_setr_ps(a.v_z, a.v_x, a.v_y, 0.0f);
    __m128 vb2 = _mm_setr_ps(b.v_y, b.v_z, b.v_x, 0.0f);
    __m128 vres2 = _mm_mul_ps(va2, vb2);

    vres2 = _mm_sub_ps(vres1, vres2);
    float tmp[4];
    _mm_storeu_ps(tmp, vres2);
    t_vector	res = { tmp[0], tmp[1], tmp[2] };
#else
	t_vector	res = new_vector(0, 0, 0);
	res.v_x = a.v_y * b.v_z - a.v_z * b.v_y;
	res.v_y = a.v_z * b.v_x - a.v_x * b.v_z;
	res.v_z = a.v_x * b.v_y - a.v_y * b.v_x;
#endif
	return (res);
}
