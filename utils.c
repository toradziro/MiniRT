/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:43:25 by ehillman          #+#    #+#             */
/*   Updated: 2021/01/08 15:17:01 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#define incrE  (2 * dy)
#define incrNE (2 * dy - 2 * dx)

void	put_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int e;
	int count;

	dx = x2 - x1;
	dy = y2 - y1;
	e = 2 * dy - dx;
	count = dx;
	my_pixel_put(data, x1, y1, color);
	while (count > 0)
	{
		count--;
		if (e > 0)
		{
			y1++;
			e += incrNE;
		}
		else
			e += incrE;
		x1++;
		my_pixel_put(data, x1, y1, color);
	}
}

void	put_square(t_data *data, int x, int y, int size, int color)
{
	int t_x;
	int t_y;

	t_x = x;
	t_y = y;
	while (t_x < (x + size))
	{
		my_pixel_put(data, t_x, t_y, color);
		t_x++;
	}
	while (t_y < (y + size))
	{
		my_pixel_put(data, t_x, t_y, color);
		t_y++;
	}
	while (t_x > x)
	{
		my_pixel_put(data, t_x, t_y, color);
		t_x--;
	}
	while (t_y > y)
	{
		my_pixel_put(data, t_x, t_y, color);
		t_y--;
	}
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->adr + (y * data->l_l + x * (data->b_p_p / 8));
	*(unsigned int*)dst = color;
}
