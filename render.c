#include "fdf.h"

void	render_background(t_data *data)
{
	int 	i;

	i = 0;
	ft_bzero(data->data_addr, sizeof(char) * SIZE);
	while (i < SIZE)
		((int*)(data->data_addr))[i++] = BACKGROUND;
}

void	render_map(t_data *data)
{
	t_dot	dot_a;
	t_dot	dot_b;
	int 	i;

	i = 0;
	while (i < data->size)
	{
		dot_a = projection(data->dot[i], data);
		if ((i + 1) % data->width != 0)
		{
			dot_b = projection(data->dot[i + 1], data);
			render_line(dot_a, dot_b, data);
		}
		if (i / data->width != data->height - 1)
		{
			dot_b = projection(data->dot[i + data->width], data);
			render_line(dot_a, dot_b, data);
		}
		i++;
	}
}

void	render_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 65, 20, TEXT_COLOR, "MENU_EPTA");
}

void	fdf_render(t_data *data)
{
	render_background(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_menu(data);
}