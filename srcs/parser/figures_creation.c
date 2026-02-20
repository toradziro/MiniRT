/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:31:18 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:24:45 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_triangle new_triangle(t_vector frt_vector, t_vector sec_point, t_vector thd_point, t_color color)
{
    t_triangle new = {0};
    t_vector tmp;

    tmp        = new_vector(0, 0, 0);
    new.a      = frt_vector;
    new.b      = sec_point;
    new.c      = thd_point;
    new.ab     = tmp;
    new.ac     = tmp;
    new.normal = tmp;
    new.color  = color;
    return (new);
}
