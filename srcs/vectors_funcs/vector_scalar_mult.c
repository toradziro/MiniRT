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

float vector_scalar_mult(t_vector a, t_vector b)
{
    float res;

#ifdef VECTORIZE
    t_vector mres;
    mres.m_vectorized = _mm_mul_ps(a.m_vectorized, b.m_vectorized);

    // SSE2-friendly horizontal sum (no _mm_hadd_ps)
    __m128 shuf = _mm_shuffle_ps(mres.m_vectorized, mres.m_vectorized, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(mres.m_vectorized, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    res         = _mm_cvtss_f32(sums);
#else
    res          = a.v_x * b.v_x + a.v_y * b.v_y + a.v_z * b.v_z;
#endif

    return (res);
}

t_vector vector_by_scalar(t_vector a, float num)
{
#ifdef VECTORIZE
    __m128   vb = _mm_setr_ps(num, num, num, num);
    t_vector res;
    res.m_vectorized = _mm_mul_ps(a.m_vectorized, vb);
#else
    t_vector res = {0, 0, 0};
    res.v_x      = a.v_x * num;
    res.v_y      = a.v_y * num;
    res.v_z      = a.v_z * num;
#endif
    return (res);
}
