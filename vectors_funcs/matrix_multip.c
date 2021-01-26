#include "../includes/MiniRT.h"

double		**matrix_multip(double **a, double **b)
{
	int		i;
	int		j;
	double	**res;

	if (!(res = matrix_decl(4)))
		killed_by_error(-1);
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
			while (j < 4)
			{
				res[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
				a[i][2] * b[2][j] + a[i][3] * b[3][j];
				j++;
			}
		i++;
	}
	return (res);
}
