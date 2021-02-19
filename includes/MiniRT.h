/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:31:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/18 21:53:37 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "vectors.h"
# include "figures.h"
# include "vplane.h"
# include "lists.h"
# include "colors.h"
# include "parser.h"
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
# define UNKNWN_ARG -5

enum e_spec
{
	S_NUL = 0b00000000,
	S_SP = 0b00000001,
	S_PL = 0b00000010,
	S_SQ = 0b00000100,
	S_CL = 0b00001000,
	S_TR = 0b00010000,
};

void		killed_by_error(int num);
void 		check_valid_name(char *str);
double		d_atoi(char *str);
double 		parse_int_part(char *str);
double 		parse_d_part(char *str);
s_color		col_parse(char *str);
s_color		check_valid_color(s_color *c);
s_scene		*ft_init_scene(void);
void		ray_trace(s_scene *scene);
s_color		intersec(s_figures *figures, s_ray *ray, s_lights *light, s_ab_light *ab_light);
s_color		find_color(s_ab_light *ab_light, s_lights *light, s_ray *ray, double min, s_vector *normal, s_figures *figures, s_color f_color, char spec);
double		sphere_intersect(s_ray *ray, s_sphere *sp);
void		free_scene(s_scene *scene);
double		plane_intersect(s_ray *ray, s_plane *plane);

int			shadow_intersec(s_figures *figures, s_ray *ray);

s_color	multip_color(s_color color, double coeff);
s_color	add_color(s_color color, s_color color_2);

#endif
