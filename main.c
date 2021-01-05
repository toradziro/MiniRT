#include "mlx.h"

typedef struct s_data {
	void	*img;
	char	*adr;
	int		b_p_p;
	int		l_l;
	int		endian;
}			t_data;

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->adr + (y * data->l_l + x * (data->b_p_p / 8));
	*(unsigned int*)dst = color;
}

void	put_square(t_data *data, int x, int y, int size, int color)
{
	int t_x;
	int t_y;

	t_x = x;
	t_y = y;
	while (t_x < (x + size))
	{
		my_pixel_put(data, t_x, t_y, color);
		t_x++;
	}
	while (t_y < (y + size))
	{
		my_pixel_put(data, t_x, t_y, color);
		t_y++;
	}
	while (t_x > x)
	{
		my_pixel_put(data, t_x, t_y, color);
		t_x--;
	}
	while (t_y > y)
	{
		my_pixel_put(data, t_x, t_y, color);
		t_y--;
	}
}
int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int x;
	int y;

	x = 50;
	y = 200;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello, graphics");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.adr = mlx_get_data_addr(img.img, &img.b_p_p, &img.l_l, &img.endian);
	put_square(&img, x, y, 100, 0x00FF00);
	put_square(&img, x + 100, y + 100, 400, 0xFF0000);
	put_square(&img, x + 500, y + 500, 100, 0x0000FF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
