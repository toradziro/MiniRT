#include "../includes/MiniRT.h"

void			killed_by_error(int num)
{
	int			error_num;

	error_num = 0;
	if (num == MALLOC_ERROR)
		error_num = write(2, "Error: malloc error.\n", 20);
	else if (num == INV_AM_OF_ARG)
		error_num = write(2, "Error: invalid amount of the arguments.\n", 40);
	else if (num == INV_FILE_NAME)
		error_num = write(2, "Error: invalid file name.\n", 26);
	else if (num == INV_COLOR)
		error_num = write(2, "Error: invalid color.\n", 22);
	else if (num == UNKNWN_ARG)
		error_num = write(2, "Error: unknown argument.\n", 25);
	else if (num == NOT_ENOUGH)
		error_num = write(2, "Error: NOT ENOUGH ARGUMENTS, JUST FIX FILE, DON'T"
						"TOUCH MY PARSER!\n", 67);
	error_num += 1;
	exit(num);
}

void			check_valid_name(char *str)
{
	int			i;

	i = 0;
	while (str[i] == '.')
		++i;
	while (((str[i] >= 32 && str[i] < 127)) && str[i] != '.' && str[i])
		++i;
	if (str[i] != '.')
		killed_by_error(INV_FILE_NAME);
	++i;
	if (str[i] != 'r' || str[i + 1] != 't')
		killed_by_error(INV_FILE_NAME);
}

void			free_fig_test(t_vec_fig *v)
{
	int			i;
	int			len;

	i = 0;
	len = v->length;
	while (i < len)
	{
		if (v->node[i].specif == S_SP)
			free((t_sphere*)v->node[i].content);
		else if (v->node[i].specif == S_PL)
			free((t_plane*)v->node[i].content);
		else if (v->node[i].specif == S_SQ)
			free((t_square*)v->node[i].content);
		else if (v->node[i].specif == S_TR)
			free((t_triangle*)v->node[i].content);
		else if (v->node[i].specif == S_CL)
			free((t_cylinder*)v->node[i].content);
		++i;
	}
	free(v->node);
}

void			free_cams(t_cameras *cam)
{
	t_cameras	*tmp;

	while (cam)
	{
		tmp = cam->next;
		free(cam);
		cam = tmp;
	}
}

void			free_light(t_lights *light)
{
	t_lights	*tmp;

	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
}
