#include "../includes/MiniRT.h"

s_lights	*new_light_node(s_point *coordinates, double intensity, s_color color)
{
	s_lights	*new;

	if (!(new = (s_lights*)malloc(sizeof(s_lights*))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->intensity = intensity;
	new->color = color;
	return (new);
}

void 		push_back_light(s_lights *list, s_point *coordinates, double intensity, s_color color)
{
	s_lights	*tmp;

	tmp = new_light_node(coordinates, intensity, color);
	while (list->next)
		list = list->next;
	list->next = tmp;
}