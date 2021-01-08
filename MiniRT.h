/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:44:34 by ehillman          #+#    #+#             */
/*   Updated: 2021/01/08 15:09:40 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"

typedef struct 	s_data {
	void		*img;
	char		*adr;
	int			b_p_p;
	int			l_l;
	int			endian;
}				t_data;

void	put_square(t_data *data, int x, int y, int size, int color);
void	my_pixel_put(t_data *data, int x, int y, int color);
void	put_line(t_data *data, int x1, int y1, int x2, int y2, int color);

#endif
