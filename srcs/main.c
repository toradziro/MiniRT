#include "includes/MiniRT.h"

int			main(int argc, char **argv)
{
	t_scene		*scene;
	int			fd;
	char		*line;
	char		*tmp;

	if (argc != 2 && argc != 3)
		killed_by_error(INV_AM_OF_ARG);
	check_valid_name(argv[1]);
	scene = ft_init_scene();
	if (!(scene->mlx = mlx_init()))
		killed_by_error(MALLOC_ERROR);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (!line[0] || line[0] == '#')
		{
			free(line);
			continue ;
		}
		tmp = line;
		parser(tmp, scene);
		free(line);
	}
	check_scene(scene);
	scene->window = mlx_new_window(scene->mlx,
	scene->width, scene->height, "MiniRT");
	if (argc == 3 && !strcmp(argv[2], "--save"))
		scene->is_save = 1;
	else if (argc == 3 && strcmp(argv[2], "--save"))
		killed_by_error(UNKNWN_ARG);
	mlx_hook(scene->window, 2, 0, press_key, scene);
	mlx_hook(scene->window, 17, 0, exit_rt, scene);
	mlx_hook(scene->window, 4, 0, mouse_press, scene);
	threads(scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}

int		exit_rt(t_scene *scene)
{
	free_scene(scene);
	exit(0);
	return (0);
}

void	check_scene(t_scene *scene)
{
	if (!scene->is_amb_l || !scene->is_cam ||
		!scene->is_figur || !scene->is_light || !scene->is_size)
		killed_by_error(NOT_ENOUGH);
}

int			mouse_press(int b, int x, int y, t_scene *scene)
{
	t_ray		ray;
	double		coefs[3];
	int			i;
	t_sphere	*sp;

	mlx_destroy_image(scene->mlx, scene->img.img);
	sp = NULL;
	i = -1;
	coefs[1] = -y + (scene->height * 0.5);
	coefs[0] = x - (scene->width * 0.5);
	coefs[2] = scene->width / (2 * tan(scene->cams->field_of_v * 0.5
				* M_PI * 0.00555555555));
	ray.orig = scene->cams->coordinates;
	ray.dir = new_vector(coefs[0], coefs[1], coefs[2]);
	ray.dir = matrix_mult(ray.dir, scene->mtrx);
	ray.dir = vector_normalise(ray.dir);
	while (++i < scene->figures->length)
		if (scene->figures->node[i].specif == S_SP)
			if (sphere_intersect(ray, scene->figures->node[i].content) > 0)
				sp = (t_sphere*)scene->figures->node[i].content;
	if (b == 1 && sp)
		++sp->radius;
	if (b == 2 && sp)
		--sp->radius;
	threads(scene);
	return (0);
}

int		press_key(int key, t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	if (key == KEY_TAB)
	{
		if (scene->cams->next)
			scene->cams = scene->cams->next;
		else
			scene->cams = scene->first_cam;
	}
	else if (key == KEY_W)
		scene->cams->coordinates.v_z += 4;
	else if (key == KEY_S)
		scene->cams->coordinates.v_z -= 4;
	else if (key == KEY_A)
		scene->cams->coordinates.v_x += 4;
	else if (key == KEY_D)
		scene->cams->coordinates.v_x -= 4;
	else if (key == KEY_Q)
	{
		scene->cams->direction.v_x += 0.05;
		scene->cams->direction = vector_normalise(scene->cams->direction);
	}
	else if (key == KEY_E)
	{
		scene->cams->direction.v_x -= 0.05;
		scene->cams->direction = vector_normalise(scene->cams->direction);
	}
	else if (key == KEY_ESC)
	{
		free_scene(scene);
		exit(0);
	}
	threads(scene);
	return (0);
}

t_scene		*ft_init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		killed_by_error(MALLOC_ERROR);
	memset(scene, 0, sizeof(t_scene));
	return (scene);
}

void		free_scene(t_scene *scene)
{
	free_cams(scene->cams);
	free_light(scene->lights);
	free_fig_test(scene->figures);
	free(scene->mlx);
	free(scene->window);
	free(scene);
}

