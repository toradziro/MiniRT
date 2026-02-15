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
#include <SDL2/SDL_scancode.h>

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

int press_key(SDL_Keysym key, t_scene* scene)
{
    switch (key.scancode)
    {
    case (SDL_SCANCODE_TAB):
    {
        scene->cams = (scene->cams->next == NULL) ? scene->first_cam : scene->cams->next;
    }
    break;
    case (SDL_SCANCODE_W):
    {
        scene->cams->coordinates.v_z += 4;
    }
    break;
    case (SDL_SCANCODE_S):
    {
        scene->cams->coordinates.v_z -= 4;
    }
    break;
    case (SDL_SCANCODE_A):
    {
        scene->cams->coordinates.v_x += 4;
    }
    break;
    case (SDL_SCANCODE_D):
    {
        scene->cams->coordinates.v_x -= 4;
    }
    break;
    case (SDL_SCANCODE_Q):
    {
        scene->cams->coordinates.v_y += 4;
    }
    break;
    case (SDL_SCANCODE_E):
    {
        scene->cams->coordinates.v_y -= 4;
    }
    break;
    case (SDL_SCANCODE_ESCAPE):
    {
        exit_rt(scene);
    }
    break;
    default:
        break;
    }
    return (0);
}
