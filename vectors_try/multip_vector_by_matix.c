#include "vectors.h"

s_vector	multip_vector_by_matix(int a, int b, int c, int d, s_vector vec)
{
	int tmp_x = (vec.x * a) + (vec.y * b);
	int tmp_y = (vec.x * c) + (vec.y * d);
	vec.x = tmp_x;
	vec.y = tmp_y;
	return (vec);
}

int main(void)
{
	int a = 6;
	int b = 7;
	int c = 0;
	int d = 9;
	s_vector vec;
	vec.x = 3;
	vec.y = 1;
	vec = multip_vector_by_matix(a, b, c, d, vec);
	printf ("Vector after lineral transformation is [%d, %d]\n", vec.x, vec.y);
}
