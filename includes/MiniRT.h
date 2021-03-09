/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:31:42 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/09 22:05:26 by ehillman         ###   ########.fr       */
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
# include "mlx_image.h"
# include "threads.h"
# include "array.h"

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
#include <sys/time.h>

#ifndef THREADS_MAX
# define THREADS_MAX 4
#endif

# define MAX(a,b)(((a)>(b))?(a):(b))
# define ABS(a)((a)>(0))?(a):(-a)

# define MIN_I 0.004

# define MALLOC_ERROR -1
# define INV_AM_OF_ARG -2
# define INV_FILE_NAME -3
# define INV_COLOR -4
# define UNKNWN_ARG -5

# define COLOR_COEFF 0.003921568627
# define MAX_COLOR 255
# define SHININESS 120.0

# define KEY_TAB 48
# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14

# define MAX_INTERSEC 100000

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
float		d_atoi(char *str);
float 		parse_int_part(char *str);
float 		parse_d_part(char *str);
s_color		col_parse(char *str);
s_color		check_valid_color(s_color *c);
s_scene		*ft_init_scene(void);
void		free_scene(s_scene *scene);

s_color		find_color(s_scene *scene, s_ray *ray, float min, s_vector normal, s_color *f_color);
s_color		intersec(s_scene *scene, s_ray ray);
float		sphere_intersect(s_ray ray, s_sphere *sp);
float		plane_intersect(s_ray ray, s_plane *plane);
float		triangle_intersec(s_ray *ray, s_triangle *triangle);
float		square_intersec(s_ray ray, s_square *sq, float min_t);

int			shadow_intersec(s_vec_fig *figures, s_lights *lights, s_vector *intersec_point, s_vector *dir_to_light);

s_color		multip_color(s_color color, float coeff);
s_color		add_color(s_color color, s_color color_2);
s_color		final_color(float coeff, s_color color, s_lights *light);
s_color		normal_color(s_color color);
s_color		anti_normal_color(s_color color);
s_color		mult_color_by_color(s_color one, s_color two);
s_color		shad_color(s_color figur, s_color ab_light);

s_phong		calc_phong(s_vector intersec_point, s_scene *scene, s_vector normal);

int		press_key(int key, s_scene *scene);

void	print_scene(s_scene *scene);
void	print_color(s_color c);
void	print_vector(s_vector v);

#endif
