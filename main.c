/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:43:29 by ehillman          #+#    #+#             */
/*   Updated: 2021/01/08 15:24:56 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

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
	put_line(&img, 150, 300, 550, 700, 0x00FF00);
	put_line(&img, 150, 400, 550, 200, 0x00FF00);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
