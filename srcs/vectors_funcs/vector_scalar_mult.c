/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar_mult.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:56 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:35 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

float			vector_scalar_mult(t_vector a, t_vector b)
{
	float		res;

#ifdef VECTORIZE
        __m128 va = _mm_setr_ps(a.v_x, a.v_y, a.v_z, 0.0f);
        __m128 vb = _mm_setr_ps(b.v_x, b.v_y, b.v_z, 0.0f);
        __m128 vres = _mm_mul_ps(va, vb);

        // SSE2-friendly horizontal sum (no _mm_hadd_ps)
        __m128 shuf = _mm_shuffle_ps(vres, vres, _MM_SHUFFLE(2, 3, 0, 1));
        __m128 sums = _mm_add_ps(vres, shuf);
        shuf = _mm_movehl_ps(shuf, sums);
        sums = _mm_add_ss(sums, shuf);
        res = _mm_cvtss_f32(sums);
#else
	    res = a.v_x * b.v_x + a.v_y * b.v_y + a.v_z * b.v_z;
#endif

	return (res);
}

t_vector		vector_by_scalar(t_vector a, float num)
{
#ifdef VECTORIZE
    __m128 va = _mm_setr_ps(a.v_x, a.v_y, a.v_z, 0.0f);
    __m128 vb = _mm_setr_ps(num, num, num, 0.0f);
    __m128 vres = _mm_mul_ps(va, vb);
    float tmp[4];
    _mm_storeu_ps(tmp, vres);
    t_vector	res = { tmp[0], tmp[1], tmp[2] };
#else
    t_vector	res = { 0, 0, 0 };
	res.v_x = a.v_x * num;
	res.v_y = a.v_y * num;
	res.v_z = a.v_z * num;
#endif
	return (res);
}
