/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:09:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:09:48 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

typedef struct	s_color {
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_phong
{
	t_vector	intersec_point;
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	halfway_dir;
	t_color		specular;
	float		spec;
}				t_phong;
#endif
