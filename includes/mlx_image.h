#ifndef MLX_IMAGE_H
# define MLX_IMAGE_H

typedef struct  	t_data {
    void      	  	*img;
    char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}					s_data;

void	my_mlx_pixel_put(s_data *data, int x, int y, int color);

#endif
