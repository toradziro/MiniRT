/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:31:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/02 19:23:34 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
//# include "mlx.h"
# include "vectors.h"
# include "figures.h"
# include "scene.h"
# include "vplane.h"
# include "lists.h"
# include "colors.h"
# include "../gnl/get_next_line.h"

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define MALLOC_ERROR -1
# define INV_AM_OF_ARG -2
# define INV_FILE_NAME -3
# define INV_COLOR -4

enum e_spec
{
	S_NUL = 0b00000000,
	S_SP = 0b00000001,
	S_PL = 0b00000010,
	S_SQ = 0b00000100,
	S_CL = 0b00001000,
	S_TR = 0b00010000,
	S_LT = 0b00100000,
	S_CM = 0b01000000,
	S_R = 0b10000000,
};

typedef struct	t_ab_light {
		s_color	color;
		double	intensity;
}				s_ab_light;

void		killed_by_error(int num);
void 		check_valid_name(char *str);
double		d_atoi(char *str);
double 		parse_int_part(char *str);
double 		parse_d_part(char *str);
s_color		col_parse(char *str);
s_color		check_valid_color(s_color *c);
void	 	parser(char *str, s_scene *scene);

#endif
