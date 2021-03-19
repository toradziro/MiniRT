#include "../includes/MiniRT.h"

s_cam_to_w		matrix_place(s_vector coor, s_vector dir)
{
	s_cam_to_w	res;
	s_vector	tmp;

	tmp = new_vector(0, 1, 0);
	tmp = cross_prod(tmp, dir);
	tmp = vector_normalise(tmp);
	res.matrix[0][0] = tmp.v_x;
	res.matrix[0][1] = tmp.v_y;
	res.matrix[0][2] = tmp.v_z;
	tmp = cross_prod(dir, tmp);
	tmp = vector_normalise(tmp);
	res.matrix[1][0] = tmp.v_x;
	res.matrix[1][1] = tmp.v_y;
	res.matrix[1][2] = tmp.v_z;
	res.matrix[2][0] = dir.v_x;
	res.matrix[2][1] = dir.v_y;
	res.matrix[2][2] = dir.v_z;
	res.matrix[3][0] = coor.v_x;
	res.matrix[3][1] = coor.v_y;
	res.matrix[3][2] = coor.v_z;
	return (res);
}

s_vector		matrix_mult(s_vector vec, s_cam_to_w m)
{
	s_vector	v;

	v = new_vector(0, 0, 0);
	v.v_x = vec.v_x * m.matrix[0][0] + vec.v_y * m.matrix[1][0] +
			vec.v_z * m.matrix[2][0] + m.matrix[3][0];
	v.v_y = vec.v_x * m.matrix[0][1] + vec.v_y * m.matrix[1][1] +
			vec.v_z * m.matrix[2][1] + m.matrix[3][1];
	v.v_z = vec.v_x * m.matrix[0][2] + vec.v_y * m.matrix[1][2] +
			vec.v_z * m.matrix[2][2] + m.matrix[3][2];
	return (v);
}

float		vec_matrix_mult_first_row(s_vector vec, s_cam_to_w c)
{
	s_vector 	tmp;

	tmp = new_vector(0, 0, 0);
	tmp = new_vector(c.matrix[0][0], c.matrix[0][1], c.matrix[0][2]);
	return (vector_scalar_mult(vec, tmp));
}

float		vec_matrix_mult_second_row(s_vector vec, s_cam_to_w c)
{
	s_vector 	tmp;

	tmp = new_vector(0, 0, 0);
	tmp = new_vector(c.matrix[1][0], c.matrix[1][1], c.matrix[1][2]);
	return (vector_scalar_mult(vec, tmp));
}
