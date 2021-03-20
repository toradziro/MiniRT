
#include "../includes/MiniRT.h"

t_cameras		*new_camera_node(t_vector coordinates, t_vector dir, float fov)
{
	t_cameras	*new;

	if (!(new = (t_cameras*)malloc(sizeof(t_cameras))))
		killed_by_error(MALLOC_ERROR);
	new->coordinates = coordinates;
	new->direction = dir;
	new->field_of_v = fov;
	new->next = NULL;
	return (new);
}

void			push_back_cam(t_cameras *list, t_cameras *new)
{
	while (list->next)
		list = list->next;
	list->next = new;
}
