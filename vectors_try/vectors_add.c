#include <stdio.h>
#include <stdlib.h>

typedef struct	t_vector {
	int x;
	int y;
}				s_vector;

int main (int argc, char **argv)
{
	if (argc != 5)
	{
		printf ("Try again!!!\n");
		return (-1);
	}
	s_vector first;
	s_vector second;
	s_vector res;
	first.x = atoi(argv[1]);
	first.y = atoi(argv[2]);
	second.x = atoi(argv[3]);
	second.y = atoi(argv[4]);
	res.x = (first.x + second.x);
	res.y = (first.y + second.y);
	printf ("New vector is [%d, %d]\n", res.x, res.y);
	return (0);
}
