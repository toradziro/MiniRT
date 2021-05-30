#include "../includes/MiniRT.h"

void	parser(char *str, t_scene *scene)
{
	if (str[0] == 'c' && str[1] == 'y')
		parse_cylinder(str + 2, scene);
	else if (str[0] == 'R')
		parse_size(str + 1, scene);
	else if (str[0] == 'A')
		parse_ambl(str + 1, scene);
	else if (str[0] == 'c')
		parse_cam(str + 1, scene);
	else if (str[0] == 'l')
		parse_light(str + 1, scene);
	else if (str[0] == 's' && str[1] == 'p')
		parse_sphere(str + 2, scene);
	else if (str[0] == 'p' && str[1] == 'l')
		parse_plane(str + 2, scene);
	else if (str[0] == 's' && str[1] == 'q')
		parse_square(str + 2, scene);
	else if (str[0] == 't' && str[1] == 'r')
		parse_triangle(str + 2, scene);
	else
		killed_by_error(UNKNWN_ARG);
}

char		*skip_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char		*skip_pattern(char *str)
{
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	if (*str < '0' && *str > '9')
		killed_by_error(UNKNWN_ARG);
	str = skip_nums(str);
	if (!*str || *str != ' ')
		killed_by_error(UNKNWN_ARG);
	str = skip_spaces(str);
	return (str);
}

char		*skip_nums(char *str)
{
	if (*str && *str == '-')
		++str;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str == '.')
	{
		str++;
		while (*str && (*str >= '0' && *str <= '9'))
			str++;
	}
	return (str);
}

t_vector		parse_coordinares(char *str)
{
	t_vector	new;

	new.v_x = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	new.v_y = d_atoi(str);
	str = skip_nums(str);
	if (*str == ',')
		str++;
	new.v_z = d_atoi(str);
	return (new);
}

void			parse_size(char *str, t_scene *scene)
{
	int			x;
	int			y;
	int			tmp_x;
	int			tmp_y;

	mlx_get_screen_size(scene->mlx, &x, &y);
	str = skip_spaces(str);
	tmp_x = (int)d_atoi(str);
	scene->width = MIN(tmp_x, x);
	str = skip_nums(str);
	str = skip_spaces(str);
	tmp_y = (int)d_atoi(str);
	scene->height = MIN(tmp_y, y);
	scene->is_size++;
}

void			parse_ambl(char *str, t_scene *scene)
{
	t_ab_light	*new;

	if (!(new = (t_ab_light*)malloc(sizeof(t_ab_light))))
		killed_by_error(MALLOC_ERROR);
	str = skip_spaces(str);
	new->intensity = d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	new->color = col_parse(str);
	new->color = multip_color(&new->color, new->intensity);
	scene->ab_light = new;
	scene->is_amb_l++;
}

void		parse_cam(char *str, t_scene *scene)
{
	t_cameras	*new;
	t_vector	dir;
	t_vector	coor;
	double		fov;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	dir = parse_coordinares(str);
	str = skip_pattern(str);
	fov = d_atoi(str);
	new = new_camera_node(coor, vector_normalise(dir), fov);
	if (!scene->cams)
	{
		scene->cams = new;
		scene->first_cam = scene->cams;
	}
	else
		push_back_cam(scene->cams, new);
	scene->is_cam++;
}

void			parse_light(char *str, t_scene *scene)
{
	t_lights	*new;
	t_vector	coor;
	double		intens;
	t_color		color;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	intens = d_atoi(str);
	str = skip_nums(str);
	str = skip_spaces(str);
	color = col_parse(str);
	new = new_light_node(coor, intens, color);
	if (!(scene->lights))
		scene->lights = new;
	else
		push_back_light(scene->lights, coor, intens, color);
	scene->is_light++;
}

void			parse_sphere(char *str, t_scene *scene)
{
	double		radius;
	t_vector	coordinates;
	t_color		color;
	t_sphere	*new;
	t_figures	*tmp;

	str = skip_spaces(str);
	coordinates = parse_coordinares(str);
	str = skip_pattern(str);
	radius = d_atoi(str) / 2.0;
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_sphere(radius, coordinates, color);
	tmp = new_figur_list((void*)new, S_SP);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}

void	 		parse_plane(char *str, t_scene *scene)
{
	t_plane		*new;
	t_vector	coor;
	t_vector	normal;
	t_color		color;
	t_figures	*tmp;

	str = skip_spaces(str);
	coor = parse_coordinares(str);
	str = skip_pattern(str);
	normal = parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_plane(coor, vector_normalise(normal), color);
	tmp = new_figur_list((void*)new, S_PL);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}

void			parse_square(char *str, t_scene *scene)
{
	t_square	*new;
	t_vector	center;
	t_vector	normal;
	double		size;
	t_color		color;
	t_figures	*tmp;

	str = skip_spaces(str);
	center = parse_coordinares(str);
	str = skip_pattern(str);
	normal = parse_coordinares(str);
	normal = vector_normalise(normal);
	str = skip_pattern(str);
	size = d_atoi(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_square(center, vector_normalise(normal), size, color);
	tmp = new_figur_list((void*)new, S_SQ);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp);
	scene->is_figur++;
	free(tmp);
}

void			parse_cylinder(char *str, t_scene *scene)
{
	t_cylinder	*new;
	t_color		color;
	t_vector	tmp;
	t_vector	tmp_n;
	t_figures	*tmp_fig;
	double		diameter;
	double		height;

	str = skip_spaces(str);
	tmp = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_n = parse_coordinares(str);
	str = skip_pattern(str);
	diameter = d_atoi(str);
	str = skip_pattern(str);
	height = d_atoi(str);
	str = skip_pattern(str);
	color = col_parse(str);
	new = new_cylinder(tmp, tmp_n, diameter, height, color);
	tmp_fig = new_figur_list((void*)new, S_CL);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp_fig);
	scene->is_figur++;
	free(tmp_fig);
}

void			parse_triangle(char *str, t_scene *scene)
{
	t_triangle	*new;
	t_color		color;
	t_vector	tmp_a;
	t_vector	tmp_b;
	t_vector	tmp_c;
	t_vector	tmp_ab;
	t_vector	tmp_ac;
	t_vector	normal;
	t_figures	*tmp_fig;

	str = skip_spaces(str);
	tmp_a = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_b = parse_coordinares(str);
	str = skip_pattern(str);
	tmp_c = parse_coordinares(str);
	str = skip_pattern(str);
	color = col_parse(str);
	tmp_ab = subs_vectors(tmp_b, tmp_a);
	tmp_ac = subs_vectors(tmp_c, tmp_a);
	new = new_triangle(tmp_a, tmp_b, tmp_c, color);
	new->normal = new_vector(0, 0, 0);
	new->ab = tmp_ab;
	new->ac = tmp_ac;
	normal = cross_prod(new->ab, new->ac);
	new->normal = vector_normalise(normal);
	tmp_fig = new_figur_list((void*)new, S_TR);
	if (!(scene->figures))
		scene->figures = new_vec_fig();
	scene->figures = add_elem_vec(scene->figures, *tmp_fig);
	scene->is_figur++;
	free(tmp_fig);
}
