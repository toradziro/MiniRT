#include "vectors.h"

int main (int argc, char **argv)
{
	if (argc != 4)
	{
		write(1, "Try again!\n", 11);
		return (-1);
	}
	int scalar;
	s_vector input;
	s_vector res;
	input.x = atoi(argv[1]);
	input.y = atoi(argv[2]);
	scalar = atoi(argv[3]);
	res.x = input.x * scalar;
	res.y = input.y * scalar;
	printf("New vector is [%d, %d]\n", res.x, res.y);
}
