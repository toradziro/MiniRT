#include "../includes/MiniRT.h"

void	killed_by_error(int num)
{
	if (num == -1)
		write(2, "Error: malloc error\n", 20);
	exit(num);
}
