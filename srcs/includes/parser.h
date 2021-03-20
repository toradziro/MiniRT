/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:38 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:21:55 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "figures.h"
# include "lists.h"
# include "mlx_image.h"
# include "array.h"

typedef struct		s_scene {
	t_cameras		*cams;
	t_cameras		*first_cam;
	t_vec_fig		*figures;
	t_lights		*lights;
	t_ab_light		*ab_light;
	t_cam_to_w		mtrx;
	t_data			img;
	void			*mlx;
	void			*window;
	int				is_save;
	int				is_cam;
	int				is_light;
	int				is_size;
	int				is_amb_l;
	int				is_figur;
	int				width;
	int				height;
	int				mouse_x;
	int				mouse_y;
}					t_scene;

void				parser(char *str, t_scene *scene);
char				*skip_spaces(char *str);
char				*skip_pattern(char *str);
char				*skip_nums(char *str);
t_vector			parse_coordinares(char *str);
void				parse_size(char *str, t_scene *scene);
void				parse_ambl(char *str, t_scene *scene);
void				parse_cam(char *str, t_scene *scene);
void				parse_light(char *str, t_scene *scene);
void				parse_sphere(char *str, t_scene *scene);
void				parse_plane(char *str, t_scene *scene);
void				parse_square(char *str, t_scene *scene);
void				parse_cylinder(char *str, t_scene *scene);
void				parse_triangle(char *str, t_scene *scene);

#endif
