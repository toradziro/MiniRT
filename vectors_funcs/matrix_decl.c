#include "../includes/MiniRT.h"

double		**matrix_decl(int num)
{
	int		i;
	int		j;
	double	**res;

	if(!(res = (double**)malloc(sizeof(double*) * num)))
		killed_by_error(-1);
	i = 0;
	while (i < num)
	{
		if (!(res[i] = (double*)malloc(sizeof(double) * num)))
			killed_by_error(-1);
		i++;
	}
	i = 0;
	j = 0;
	while (i < num)
	{
		j = 0;
		while (j < num)
		{
			res[i][j] = 0;
			j++;
		}
		i++;
	}
	return (res);
}
