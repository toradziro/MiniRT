#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "vectors.h"
# include "figures.h"
# include "lists.h"
# include "colors.h"
# include "parser.h"
# include "../gnl/get_next_line.h"
# include "mlx_image.h"
# include "threads.h"
# include "array.h"
# include "intersect.h"

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# ifndef THREADS_MAX
#  define THREADS_MAX 4
# endif

# define MAX(a,b)(((a)>(b))?(a):(b))
# define MIN(a,b)(((a)<(b))?(a):(b))

# define ABS(a)((a)>(0))?(a):(-a)

# define MIN_I 0.004

# define MALLOC_ERROR -1
# define INV_AM_OF_ARG -2
# define INV_FILE_NAME -3
# define INV_COLOR -4
# define UNKNWN_ARG -5
# define NOT_ENOUGH -6

# define COLOR_COEFF 0.003921568627
# define MAX_COLOR 255
# define SHININESS 100.0

# define KEY_TAB 48
# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14

# define MAX_INTERSEC 100000

enum	e_spec
{
	S_NUL = 0b00000000,
	S_SP = 0b00000001,
	S_PL = 0b00000010,
	S_SQ = 0b00000100,
	S_CL = 0b00001000,
	S_TR = 0b00010000,
};

void		killed_by_error(int num);
void		check_valid_name(char *str);
double		d_atoi(char *str);
double		parse_int_part(char *str);
double		parse_d_part(char *str);
t_color		col_parse(char *str);
t_color		check_valid_color(t_color *c);
t_scene		*ft_init_scene(void);
void		free_scene(t_scene *scene);

t_color		find_color(t_scene *scene, t_ray ray,
			double min, t_vector *normal, t_color *f_color);
t_color		intersec(t_scene *scene, t_ray ray);
void		ray_switch(t_figures *tmp, t_scene
			*scene, double *min, t_ray ray, t_color *c_tmp);

int			shadow_intersec(t_vec_fig *figures, t_vector
			*intersec_point, t_vector *dir_to_light);

t_color		multip_color(t_color *color, double coeff);
t_color		add_color(t_color *color, t_color *color_s);
t_color		shad_color(t_color *figur, t_color *ab_light);

t_phong		calc_phong(t_vector intersec_point,
			t_scene *scene, t_vector normal);

int			press_key(int key, t_scene *scene);
int			mouse_press(int b, int x, int y, t_scene *scene);

void		check_scene(t_scene *scene);

void		free_cams(t_cameras *cam);
void		free_light(t_lights *light);

void		save_to_bmp(t_scene *scene);
void		init_head(char *head, t_scene *scene, int file_size);

int			exit_rt(t_scene *scene);

void		save_to_bmp(t_scene *scene);
#endif
