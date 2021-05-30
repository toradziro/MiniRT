#include "includes/MiniRT.h"

void		save_to_bmp(t_scene *scene)
{
	int		fd;
	char	filler_head[54];
	int		row;
	int		file_size;

	memset(filler_head, 0, 54);
	file_size = 54 + 4 * scene->width * scene->height;
	init_head(filler_head, scene, file_size);
	fd = open("screen.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	write(fd, filler_head, 54);
	row = scene->height - 1;
	while (row >= 0)
	{
		write(fd, scene->img.addr + row *
		scene->img.line_length, scene->width * 4);
		--row;
	}
	close(fd);
}

void		init_head(char *head, t_scene *scene, int file_size)
{
	head[0] = 'B';
	head[1] = 'M';
	head[2] = (char)(file_size);
	head[3] = (char)(file_size >> 8);
	head[4] = (char)(file_size >> 16);
	head[5] = (char)(file_size >> 24);
	head[10] = 54;
	head[14] = 40;
	head[18] = (char)(scene->width);
	head[19] = (char)(scene->width >> 8);
	head[20] = (char)(scene->width >> 16);
	head[21] = (char)(scene->width >> 24);
	head[22] = (char)(scene->height);
	head[23] = (char)(scene->height >> 8);
	head[24] = (char)(scene->height >> 16);
	head[25] = (char)(scene->height >> 24);
	head[26] = 1;
	head[28] = 32;
}
