/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:07 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:34:18 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTERSECT_H
#define MINIRT_INTERSECT_H

void  triangle_start(t_scene* scene, t_triangle* tr, float* min, t_ray ray, t_color* c_tmp);
float triangle_intersec(t_ray ray, t_triangle* triangle);

#endif
