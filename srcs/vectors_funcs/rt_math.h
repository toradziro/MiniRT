#pragma once

#include "rt_math.h"
#include <math.h>
#include <immintrin.h>

typedef struct s_vector
{
    float v_x;
    float v_y;
    float v_z;
} t_vector;

typedef struct s_ray
{
    t_vector dir;
    t_vector orig;
} t_ray;

__attribute__((always_inline)) static inline t_vector		new_vector(float x, float y, float z)
{
	t_vector	new_vec;

	new_vec.v_x = x;
	new_vec.v_y = y;
	new_vec.v_z = z;
	return (new_vec);
}

__attribute__((always_inline)) static inline t_vector		add_vectors(t_vector a, t_vector b)
{
	t_vector res = new_vector(0, 0, 0);
	res.v_x = a.v_x + b.v_x;
	res.v_y = a.v_y + b.v_y;
	res.v_z = a.v_z + b.v_z;

	return (res);
}

__attribute__((always_inline)) static inline t_vector		subs_vectors(t_vector a, t_vector b)
{
	t_vector res = new_vector(0, 0, 0);
	res.v_x = a.v_x - b.v_x;
	res.v_y = a.v_y - b.v_y;
	res.v_z = a.v_z - b.v_z;

	return (res);
}

__attribute__((always_inline)) static inline float			vector_scalar_mult(t_vector a, t_vector b)
{
	float		res;
	res = a.v_x * b.v_x + a.v_y * b.v_y + a.v_z * b.v_z;

	return (res);
}

__attribute__((always_inline)) static inline t_vector		vector_by_scalar(t_vector a, float num)
{
    t_vector	res = { 0, 0, 0 };
	res.v_x = a.v_x * num;
	res.v_y = a.v_y * num;
	res.v_z = a.v_z * num;

	return (res);
}

__attribute__((always_inline)) static inline float	vector_length(t_vector v)
{
	return sqrt(vector_scalar_mult(v, v));
}

__attribute__((always_inline)) static inline t_vector		vector_normalise(t_vector v)
{
	float		len_coeff;

	len_coeff = 1 / vector_length(v);
	return vector_by_scalar(v, len_coeff);
}

__attribute__((always_inline)) static inline t_vector		cross_prod(t_vector b, t_vector a)
{
	t_vector	res = new_vector(0, 0, 0);
	res.v_x = a.v_y * b.v_z - a.v_z * b.v_y;
	res.v_y = a.v_z * b.v_x - a.v_x * b.v_z;
	res.v_z = a.v_x * b.v_y - a.v_y * b.v_x;

	return (res);
}
