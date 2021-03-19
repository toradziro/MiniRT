#include "../includes/MiniRT.h"

/*
A           0.3                255,0,120
c           0,0,-1               0,0,1               60
*/

void	print_scene(s_scene *scene)
{
	s_scene *tmp = scene;

	while (scene->figures && scene->figures->specif == S_SP)
	{
		s_sphere *sp_tmp = (s_sphere*)tmp->figures->content;
		printf("----------SPHERE IS------------\n");
		print_vector(sp_tmp->coordinates);
		print_color(sp_tmp->color);
		printf("%f\n\n\n", sp_tmp->radius);
		tmp->figures = tmp->figures->next;
	}

	while (scene->figures && scene->figures->specif == S_PL)
	{
		s_plane *pl_tmp = (s_plane*)tmp->figures->content;
		printf("----------PLANE IS------------\n");
		print_vector(pl_tmp->coordinates);
		print_vector(pl_tmp->normal);
		print_color(pl_tmp->color);
		printf("\n\n\n");
		tmp->figures = tmp->figures->next;
	}

	printf("----------SI~E IS------------\n");
	printf("%d, %d\n\n\n", tmp->width, tmp->height);

	while (scene->lights)
	{
		printf("----------LIGHT IS------------\n");
		print_vector(tmp->lights->coordinates);
		print_color(tmp->lights->color);
		printf("%f\n\n\n", tmp->lights->intensity);
		tmp->lights = tmp->lights->next;
	}

	printf("----------AMBL IS------------\n");
	print_color(tmp->ab_light->color);
	printf("%f\n\n\n", tmp->ab_light->intensity);

	while (scene->cams)
	{
		printf("----------CAM IS------------\n");
		print_vector(tmp->cams->coordinates);
		print_vector(tmp->cams->direction);
		printf("%f\n\n\n", tmp->cams->field_of_v);
		tmp->cams = tmp->cams->next;
	}
}

void	print_vector(s_vector v)
{
	printf("x = %f\ty = %f\tz = %f\n\n", v.v_x, v.v_y, v.v_z);
}

void	print_color(s_color c)
{
	printf("r = %f\ng = %f\nb = %f\n", c.r, c.g, c.b);
}
