#ifndef VPLANE_H
# define VPLANE_H
# include "MiniRT.h"

typedef struct	t_vplane {
		float	width;
		float	hieght;
		float	x_pixel;
		float	y_pixel;
}				s_vplane;

//s_vplane		*get_view_plane(float width, float height, float fov);
//void			ray_trace(void *mlx, void *window, s_scene *scene);

#endif
