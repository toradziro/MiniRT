/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_add_substract.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:38:06 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:38:37 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"
#include <immintrin.h>

t_vector		add_vectors(t_vector a, t_vector b)
{
#ifdef VECTORIZE
    //--_mm_set_ps(w, z, y, x)
    __m128 va = _mm_set_ps(0.0f, a.v_x, a.v_y, a.v_z);
    __m128 vb = _mm_set_ps(0.0f, b.v_x, b.v_y, b.v_z);
    __m128 vres = _mm_add_ps(va, vb);
    //-- tmp[0] = x` - `tmp[1] = y`, - `tmp[2] = z`, - `tmp[3] = w`
    // float* tmp = (float*)&vres;
    float tmp[4];
    _mm_storeu_ps(tmp, vres);
    t_vector	res = { tmp[2], tmp[1], tmp[0] };
#else
	t_vector res = new_vector(0, 0, 0);
	res.v_x = a.v_x + b.v_x;
	res.v_y = a.v_y + b.v_y;
	res.v_z = a.v_z + b.v_z;
#endif
	return (res);
}

t_vector		subs_vectors(t_vector a, t_vector b)
{
#ifdef VECTORIZE
        //--_mm_set_ps(w, z, y, x)
        __m128 va = _mm_set_ps(0.0f, a.v_x, a.v_y, a.v_z);
        __m128 vb = _mm_set_ps(0.0f, b.v_x, b.v_y, b.v_z);
        __m128 vres = _mm_sub_ps(va, vb);
        //-- tmp[0] = x` - `tmp[1] = y`, - `tmp[2] = z`, - `tmp[3] = w`
        // float* tmp = (float*)&vres;
        float tmp[4];
        _mm_storeu_ps(tmp, vres);
        t_vector	res = { tmp[2], tmp[1], tmp[0] };
#else
	t_vector res = new_vector(0, 0, 0);
	res.v_x = a.v_x - b.v_x;
	res.v_y = a.v_y - b.v_y;
	res.v_z = a.v_z - b.v_z;
#endif
	return (res);
}
