#include "fdf.h"

void	render_background(t_data *data)
{
	int 	i;
	int 	*image;

	i = 0;
	ft_bzero(data->data_addr, SIZE * data->bits_per_pixel / 8);
	image = (int*)(data->data_addr);
	while (i < SIZE)
		image[i++] = BACKGROUND;
}

void	fdf_render(t_data *data)
{
	render_background(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}