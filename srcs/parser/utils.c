/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:32:04 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:24:22 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float		d_atoi(char *str)
{
	int		i;
	int		sign;
	float	res;

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
	if (!str[i])
		return (res * (float)sign);
	if (str[i] == '.')
	{
		++i;
		res += parse_d_part(&str[i]);
	}
	return (res * (float)sign);
}

float		parse_int_part(char *str)
{
	int		i;
	float	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (res);
}

float		parse_d_part(char *str)
{
	int		i;
	float	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	res /= pow(10, i);
	return (res);
}

t_color		col_parse(char *str)
{
	t_color	res;
	int		i;

	i = 0;
	if (str[i] < '0' || str[i] > '9')
		killed_by_error(INV_COLOR);
	res.r = (int)parse_int_part(&str[i]);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		++i;
	if (str[i] == ',')
		++i;
	else
		killed_by_error(INV_COLOR);
	if (str[i] < '0' || str[i] > '9')
		killed_by_error(INV_COLOR);
	res.g = (int)parse_int_part(&str[i]);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		++i;
	if (str[i] != ',')
		killed_by_error(INV_COLOR);
	++i;
	if (str[i] < '0' || str[i] > '9')
		killed_by_error(INV_COLOR);
	res.b = (int)parse_int_part(&str[i]);
	return (check_valid_color(&res));
}

t_color		check_valid_color(t_color *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
	if (c->r < 0)
		c->r = 0;
	if (c->g < 0)
		c->g = 0;
	if (c->b < 0)
		c->b = 0;
	return (*c);
}
