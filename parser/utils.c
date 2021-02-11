#include "../includes/MiniRT.h"

double		d_atoi(char *str)
{
	int 	i;
	int 	sign;
	double	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	res = parse_int_part(&str[i]);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		++i;
	if (str[i] == '.')
	{
		++i;
		res += parse_d_part(&str[i]);
	}
	return (res * (double)sign);
}

double 		parse_int_part(char *str)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while ((str[i] >= '0' && str[i] <= '9') && *str)
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (res);
}

double 		parse_d_part(char *str)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	res /= pow(10, i);
	return (res);
}

s_color			col_parse(char *str)
{
	s_color		res;
	int			i;

	i = 0;
	if (str[i] < '0' || str[i] > '9') //add new error
		killed_by_error(INV_COLOR);
	res.r = (int)parse_int_part(&str[i]);
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ')
		++i;
	while (str[i] == ',' || str[i] == ' ')
		++i;
	if (str[i] < '0' || str[i] > '9') //add new error
		killed_by_error(INV_COLOR);
	res.g = (int)parse_int_part(&str[i]);
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ')
		++i;
	while (str[i] == ',' || str[i] == ' ')
		++i;
	if (str[i] < '0' || str[i] > '9') //add new error
		killed_by_error(INV_COLOR);
	res.b = (int)parse_int_part(&str[i]);
	return (check_valid_color(&res));
}

s_color			check_valid_color(s_color *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
	return (*c);
}
