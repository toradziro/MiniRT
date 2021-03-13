/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:10:13 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/11 19:42:12 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "figures.h"
# include "lists.h"
# include "mlx_image.h"
# include "array.h"

typedef struct		t_scene {
	s_cameras		*cams;
	s_cameras		*first_cam;
	s_vec_fig		*figures;
	s_lights		*lights;
	s_ab_light		*ab_light;
	s_cam_to_w		mtrx;
	s_data			img;
	void			*mlx;
	void			*window;
	int 			is_save;
	int 			is_cam;
	int 			is_light;
	int 			is_size;
	int 			is_amb_l;
	int 			is_figur;
	int				width;
	int				height;
}					s_scene;

void 			parser(char *str, s_scene *scene);
char			*skip_spaces(char *str);
char			*skip_pattern(char *str);
char			*skip_nums(char *str);
s_vector		parse_coordinares(char *str);
void	 		parse_size(char *str, s_scene *scene);
void 			parse_ambl(char *str, s_scene *scene);
void 			parse_cam(char *str, s_scene *scene);
void	 		parse_light(char *str, s_scene *scene);
void 			parse_sphere(char *str, s_scene *scene);
void	 		parse_plane(char *str, s_scene *scene);
void			parse_square(char *str, s_scene *scene);
void			parse_cylinder(char *str, s_scene *scene);
void			parse_triangle(char *str, s_scene *scene);

#endif
