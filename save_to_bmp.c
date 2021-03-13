#include "includes/MiniRT.h"

void 		save_to_bmp(s_scene *scene)
{
	int 					fd;
	char					filler_head[54];
	int						pixels_pr;
	int 					fill_row;
	int 					row;
	const unsigned char		zeros[3] = {0, 0, 0};

	//bitmap header 54

	memset(filler_head, 0, 54);
	filler_head[0] = 'B';
	filler_head[1] = 'M';
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
	filler_head[28] = 24; //bits_per_pixel
	pixels_pr = scene->width * 4; //rgb
	fill_row = (4 - (pixels_pr % 4)) % 4;
	//filler_head[2] = 54 + (pixels_pr + fill_row) * scene->height;
	*(unsigned int*)(&filler_head[2]) = 54 + 3 * scene->width * scene->height;
	fd = open("screen.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666);

	write(fd, filler_head, 54);

	row = scene->height;
	while (row >= 0)
	{
		write(fd, scene->img.addr + row * scene->width * 4, scene->width * 4);
		write(fd, zeros, fill_row);
		--row;
	}
	close (fd);
}