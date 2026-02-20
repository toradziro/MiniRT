/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 00:03:46 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:06:29 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/MiniRT.h"
#include "vectors_funcs/rt_math.h"
#include "window/window.h"

// int				mouse_press(int b, int x, int y, t_scene *scene)
// {
// 	// t_ray		ray;
// 	// float		coef;
// 	// int			i;
// 	// t_sphere	*sp;

// 	// mlx_clear_window(scene->mlx, scene->window);
// 	// mlx_destroy_image(scene->mlx, scene->img.img);
// 	// sp = NULL;
// 	// i = -1;
// 	// coef = scene->width / (2 * tan(scene->cams->field_of_v * 0.5 *
// 	// 			M_PI * 0.00555555555));
// 	// ray.orig = scene->cams->coordinates;
// 	// ray.dir = new_vector((x - (scene->width * 0.5)),
// 	// 			(-y + (scene->height * 0.5)), coef);
// 	// ray.dir = matrix_mult(ray.dir, scene->mtrx);
// 	// while (++i < scene->figures->length)
// 	// 	if (scene->figures->node[i].specif == S_SP)
// 	// 		if (sphere_intersect(ray, scene->figures->node[i].content)
// > 0)
// 	// 			sp = (t_sphere*)scene->figures->node[i].content;
// 	// if (b == 1 && sp)
// 	// 	++sp->radius;
// 	// if (b == 2 && sp)
// 	// 	--sp->radius;
// 	// threads(scene);
// 	return (0);
// }

int press_key(t_key key, t_scene* scene)
{
    t_vector forward = scene->cams->direction;
    t_vector up      = new_vector(0, 1, 0);
    t_vector right   = cross_prod(&forward, &up);

    switch (key)
    {
    case (RT_SCANCODE_TAB):
    {
        scene->cams = (scene->cams->next == NULL) ? scene->first_cam : scene->cams->next;
    }
    break;
    case (RT_SCANCODE_W):
    {
        forward                  = vector_by_scalar(&forward, 4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &forward);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_S):
    {
        forward                  = vector_by_scalar(&forward, -4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &forward);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_A):
    {
        right                    = vector_by_scalar(&right, 4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &right);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_D):
    {
        right                    = vector_by_scalar(&right, -4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &right);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_Q):
    {
        up                       = vector_by_scalar(&up, 4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &up);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_E):
    {
        up                       = vector_by_scalar(&up, -4);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &up);
        memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
    }
    break;
    case (RT_SCANCODE_ESCAPE):
    {
        exit_rt(scene);
    }
    break;
    default:
        break;
    }
    // printf("pos: %f,%f,%f\ndir: %f,%f,%f",
    //     scene->cams->coordinates.v_x,
    //     scene->cams->coordinates.v_y,
    //     scene->cams->coordinates.v_z,
    //     scene->cams->direction.v_x,
    //     scene->cams->direction.v_y,
    //     scene->cams->direction.v_z
    //     );
    return (0);
}
