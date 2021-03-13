#include "../includes/MiniRT.h"

s_lights		*new_light_node(s_vector coordinates, float intensity, s_color color)
{
	s_lights	*new;
	s_vector	tmp = {0, 0, 0};

	if (!(new = (s_lights*)malloc(sizeof(s_lights))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->intensity = intensity;
	new->color = color;
	new->light_dir = tmp;
	new->next = NULL;
	return (new);
}

void 			push_back_light(s_lights *list, s_vector coordinates, float intensity, s_color color)
{
	s_lights	*tmp;

	tmp = new_light_node(coordinates, intensity, color);
	while (list->next)
		list = list->next;
	list->next = tmp;
}
