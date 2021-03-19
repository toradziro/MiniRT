#include "includes/MiniRT.h"

void 		save_to_bmp(s_scene *scene)
{
	int 					fd;
	char					filler_head[54];
	int 					row;
	int 					file_size = 54 + 4 * scene->width * scene->height;

	//bitmap header 54

	memset(filler_head, 0, 54);
	filler_head[0] = 'B';
	filler_head[1] = 'M';
	filler_head[2] = (unsigned char)(file_size);
	filler_head[3] = (unsigned char)(file_size >> 8);
	filler_head[4] = (unsigned char)(file_size >> 16);
	filler_head[5] = (unsigned char)(file_size >> 24);
	filler_head[10] = 54; //pixel_data_offset
	filler_head[14] = 40; //head_size
	filler_head[18] = (unsigned char)(scene->width);
	filler_head[19] = (unsigned char)(scene->width >> 8);
	filler_head[20] = (unsigned char)(scene->width >> 16);
	filler_head[21] = (unsigned char)(scene->width >> 24);
	filler_head[22] = (unsigned char)(scene->height);
	filler_head[23] = (unsigned char)(scene->height >> 8);
	filler_head[24] = (unsigned char)(scene->height >> 16);
	filler_head[25] = (unsigned char)(scene->height >> 24);
	filler_head[26] = 1; //planes
	filler_head[28] = 32; //bits_per_pixel
	fd = open("screen.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666);

	write(fd, filler_head, 54);

	row = scene->height - 1;
	while (row >= 0)
	{
		write(fd, scene->img.addr + row * scene->img.line_length, scene->width * 4);
		--row;
	}
	close (fd);
}