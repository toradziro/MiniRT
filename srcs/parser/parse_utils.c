/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 22:22:13 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 22:42:10 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

char			*skip_spaces(char *str)
{
	if (*str != ' ')
		killed_by_error(UNKNWN_ARG);
	while (*str && *str == ' ')
		str++;
	if (*str != '-' && (*str > '9' || *str < '0'))
		killed_by_error(UNKNWN_ARG);
	return (str);
}

char			*skip_pattern(char *str)
{
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (!*str || *str != ' ')
		killed_by_error(UNKNWN_ARG);
	str = skip_spaces(str);
	return (str);
}

char			*skip_nums(char *str)
{
	if (*str && *str == '-')
		++str;
	if (*str > '9' && *str < '0')
		killed_by_error(UNKNWN_ARG);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str == '.')
	{
		str++;
		while (*str && (*str >= '0' && *str <= '9'))
			str++;
	}
	return (str);
}

t_vector		parse_coordinares(char *str)
{
	t_vector	new;

	new.v_x = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	new.v_y = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	new.v_z = d_atoi(str);
	return (new);
}

t_color			new_color(int r, int g, int b)
{
	t_color		new;

	new.r = r;
	new.r = g;
	new.b = b;
	return (new);
}
