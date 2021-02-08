#include "../includes/MiniRT.h"

s_figures		*new_figur_list(void *content, char spec)
{
	s_figures	*new;

	if (!(new = (s_figures*)malloc(sizeof(s_figures))))
		killed_by_error(MALLOC_ERROR);
	if (spec == 's')
	{
		new->content = (s_sphere*)content;
		new->specif = spec;
	}
	new->next = NULL;
	return (new);
}

void		push_back_figur(s_figures *start, void *content, char spec)
{
	s_figures	*new;

	new = new_figur_list(content, spec);
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}

//int main(void)
//{
//	s_sphere *new_one = new_sphere(new_point(1, 1, 1), 22);
//	s_sphere *new_two = new_sphere(new_point(2, 2, 2), 44);
//	s_sphere *tmp;
//	s_figures *list_spheres = new_figur_list(new_one, 's');
//	push_back_figur(list_spheres, new_two, 's');
//	while (list_spheres)
//	{
//		if (list_spheres->specif == 's')
//		{
//			tmp = (s_sphere*)list_spheres->content;
//			printf("----------SPHERE----------\ncoordinates are: x = %f, y = "
//		  "%f, z = %f\ndiameter is %f", list_spheres->content->coordinates->p_x, list_spheres->content->coordinates->p_y, list_spheres->
//			content->coordinates->p_z, list_spheres->
//			content->radius);
//			printf("----------SPHERE----------\n"
//		  			"coordinates are: x = %f\n",
//				   	tmp->coordinates->p_x);
//		}
//	}
//}