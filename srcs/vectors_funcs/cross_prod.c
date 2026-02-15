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

t_vector cross_prod(t_vector b, t_vector a)
{
#ifdef VECTORIZE
    t_vector res;

    const __m128 a_yzx = _mm_shuffle_ps(a.m_vectorized, a.m_vectorized, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 a_zxy = _mm_shuffle_ps(a.m_vectorized, a.m_vectorized, _MM_SHUFFLE(3, 1, 0, 2));
    const __m128 b_yzx = _mm_shuffle_ps(b.m_vectorized, b.m_vectorized, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 b_zxy = _mm_shuffle_ps(b.m_vectorized, b.m_vectorized, _MM_SHUFFLE(3, 1, 0, 2));

    res.m_vectorized = _mm_sub_ps(_mm_mul_ps(a_yzx, b_zxy), _mm_mul_ps(a_zxy, b_yzx));
#else
    t_vector res = new_vector(0, 0, 0);
    res.v_x      = a.v_y * b.v_z - a.v_z * b.v_y;
    res.v_y      = a.v_z * b.v_x - a.v_x * b.v_z;
    res.v_z      = a.v_x * b.v_y - a.v_y * b.v_x;
#endif
    return (res);
}
