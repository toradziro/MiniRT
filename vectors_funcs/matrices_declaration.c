#include "vectors.h"

double		**matrix_decl(int num)
{
	int		i;
	int		j;
	double	**res;

	if(!(res = (double**)malloc(sizeof(double*) * num)))
		return (NULL);
	i = 0;
	while (i < num)
	{
		if (!(res[i] = (double*)malloc(sizeof(double) * num)))
			return (NULL);
		i++;
	}
	i = 0;
	j = 0;
	while (i < num)
	{
		j = 0;
		while (j < num)
		{
			res[i][j] = (double)j;
			j++;
		}
		i++;
	}
	return (res);
}
