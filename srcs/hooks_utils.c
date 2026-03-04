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

void process_scene(t_key key, t_application* application)
{
    t_scene* scene = &application->curr_scene;
    t_vector forward = scene->cams->direction;
    t_vector up = scene->cams->up;
    t_vector right   = cross_prod(&forward, &up);

    const float rotation_speed = 1.2 * scene->dt;
    const float movement_speed = 300 * scene->dt;

    switch (key)
    {
    case (RT_SCANCODE_TAB):
    {
        scene->cams = (scene->cams->next == NULL) ? scene->first_cam : scene->cams->next;
    }
    break;
    case (RT_SCANCODE_W):
    {
        forward                  = vector_by_scalar(&forward, movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &forward);
    }
    break;
    case (RT_SCANCODE_S):
    {
        forward                  = vector_by_scalar(&forward, -movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &forward);
    }
    break;
    case (RT_SCANCODE_A):
    {
        right                    = vector_by_scalar(&right, movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &right);
    }
    break;
    case (RT_SCANCODE_D):
    {
        right                    = vector_by_scalar(&right, -movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &right);
    }
    break;
    case (RT_SCANCODE_Q):
    {
        up                       = vector_by_scalar(&up, movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &up);
    }
    break;
    case (RT_SCANCODE_E):
    {
        up                       = vector_by_scalar(&up, -movement_speed);
        scene->cams->coordinates = add_vectors(&scene->cams->coordinates, &up);
    }
    break;
    case (RT_SCANCODE_ARROW_UP):
    {
        scene->cams->pitch += rotation_speed;
    }
    break;
    case (RT_SCANCODE_ARROW_DOWN):
    {
        scene->cams->pitch -= rotation_speed;
    }
    break;
    case (RT_SCANCODE_ARROW_LEFT):
    {
        scene->cams->yaw -= rotation_speed;
    }
    break;
    case (RT_SCANCODE_ARROW_RIGHT):
    {
        scene->cams->yaw += rotation_speed;
    }
    break;
    case (RT_SCANCODE_ESCAPE):
    {
        application->switch_to_menu_triggered = true;
    }
    break;
    default:
        break;
    }
    scene->need_update_mtx = true;
    memset(scene->pixels_avg, 0, scene->width * scene->height * sizeof(t_accum_data));
}


void process_menu(t_key key, t_application* application)
{
    switch (key)
    {
    case (RT_SCANCODE_ARROW_UP):
    {
        application->menu_state.selected_item--;
    }
    break;
    case (RT_SCANCODE_ARROW_DOWN):
    {
        application->menu_state.selected_item++;
    }
    break;
    case (RT_SCANCODE_ESCAPE):
    {
        application->is_running = false;
    }
    break;
    case (RT_SCANCODE_ENTER):
    {
        application->scene_loading_triggered = true;
    }
    break;
    default:
        break;
    }
}

int press_key(t_key key, t_application* application)
{
    switch(application->curr_app_state)
    {
        case Menu: process_menu(key, application); break;
        case Scene: process_scene(key, application); break;
        default: break;
    }
    return (0);
}
