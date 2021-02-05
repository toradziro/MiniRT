#include "../includes/MiniRT.h"

void	killed_by_error(int num)
{
	if (num == -1)
		write(2, "Error: malloc error.\n", 20);
	else if (num == -2)
		write(2, "Error: invalid amount of the arguments.\n", 40);
	else if (num == -3)
		write(2, "Error: invalid file name.\n", 26);
	exit(num);
}

void 		check_valid_name(char *str)
{
	int		i;

	i = 0;
	while (((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')) && str[i] != '.' && str[i])
		++i;
	if (str[i] != '.')
		killed_by_error(-3);
	++i;
	if (str[i] != 'r' && str[i + 1] != 't')
		killed_by_error(-3);
}