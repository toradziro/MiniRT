#include "../includes/MiniRT.h"

s_cameras		*new_camera_node(s_point *coordinates, s_vector *dir, double fov)
{
	s_cameras	*new;

	if (!(new = (s_cameras*)malloc(sizeof(s_cameras))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->direction = dir;
	new->field_of_v = fov;
	new->next = NULL;
	return (new);
}

void 			push_back_cam(s_cameras *list, s_point *coordinates, s_vector *dir, double fov)
{
	s_cameras	*tmp;

	tmp = new_camera_node(coordinates, dir, fov);
	while (list->next)
		list = list->next;
	list->next = tmp;
}