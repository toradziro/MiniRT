#include <stdio.h>
#include "vectors.h"

void	print_m(double **m)
{
	int i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", m[i][j]);
			j++;
		}
		printf ("\n");
		i++;
	}
	printf("\n\n\n");
}

int main(void)
{
	int		i;
	int		j;
	double **a;
	double **b;
	double **c;

	i = 0;
	a = matrix_decl(4);
	b = matrix_decl(4);
	while (i < 4)
	{
		a[0][i] = (double)i;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		b[1][i] = (double)i;
		i++;
	}
	c = matrix_multip(a, b);
	print_m(a);
	print_m(b);
	print_m(c);
}
