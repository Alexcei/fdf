#include "fdf.h"

int		fdf_init(t_data *data, t_map *map, t_mouse *mouse, t_camera *camera)
{
	ft_bzero(camera, sizeof(camera));
	ft_bzero(mouse, sizeof(mouse));
	ft_bzero(data, sizeof(data));
	ft_bzero(map, sizeof(map));
	data->camera = camera;
	data->mouse = mouse;
	data->map = map;
	if (!(data->mlx = mlx_init()) ||
		!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF")) ||
		!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	return (1);
}

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

int 	main(int ac, char **av)
{
	t_camera	camera;
	t_mouse		mouse;
	t_data		data;
	t_map		map;
	int			fd;

	if (ac == 1)
		print_error("error: not enough arguments");
	if (ac > 2)
		print_error("error: too many arguments");
	if (!fdf_init(&data, &map, &mouse, &camera))
		print_error("error: initialization");
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !fdf_read_file(fd, &data))
		print_error("error: reading fail");
	fdf_render(&data);
	//fdf_control(&data);
	mlx_loop(&data.mlx);
	return (0);
}