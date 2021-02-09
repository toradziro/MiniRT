#include "../includes/MiniRT.h"

void	killed_by_error(int num)
{
	if (num == MALLOC_ERROR)
		write(2, "Error: malloc error.\n", 20);
	else if (num == INV_AM_OF_ARG)
		write(2, "Error: invalid amount of the arguments.\n", 40);
	else if (num == INV_FILE_NAME)
		write(2, "Error: invalid file name.\n", 26);
	else if (num == INV_COLOR)
		write(2, "Error: invalid color.\n", 22);
	else if (num == UNKNWN_ARG)
		write(2, "Error: unknown argument.\n", 25);
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
		killed_by_error(INV_FILE_NAME);
	++i;
	if (str[i] != 'r' && str[i + 1] != 't')
		killed_by_error(INV_FILE_NAME);
}