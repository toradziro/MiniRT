#ifndef VPLANE_H
# define VPLANE_H
# include "MiniRT.h"

typedef struct	t_vplane {
		double	width;
		double	hieght;
		double	x_pixel;
		double	y_pixel;
}				s_vplane;

//s_vplane		*get_view_plane(double width, double height, double fov);
//void			ray_trace(void *mlx, void *window, s_scene *scene);

#endif
