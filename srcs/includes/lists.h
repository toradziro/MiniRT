/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:16 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:19:19 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct		s_figures{
	void			*content;
	char			specif;
}					t_figures;

typedef struct		s_cameras{
	t_vector		coordinates;
	t_vector		direction;
	void			*next;
	float			field_of_v;
}					t_cameras;

typedef struct		s_lights {
	t_vector		coordinates;
	t_vector		light_dir;
	void			*next;
	t_color			color;
	float			intensity;
}					t_lights;

typedef struct		s_ab_light {
	t_color			color;
	float			intensity;
}					t_ab_light;

void				push_back_cam(t_cameras *list, t_cameras *cam);
t_figures			*new_figur_list(void *content, char spec);
t_cameras			*new_camera_node(t_vector coordinates,
					t_vector dir, float fov);
t_lights			*new_light_node(t_vector coordinates,
					float intensity, t_color color);
void				push_back_light(t_lights *list, t_vector coordinates,
					float intensity, t_color color);

#endif
