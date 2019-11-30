#include "fdf.h"

int		fdf_init(t_data *data, t_mouse *mouse, t_camera *camera)
{
	ft_bzero(camera, sizeof(t_camera));
	ft_bzero(mouse, sizeof(t_mouse));
	ft_bzero(data, sizeof(t_data));
	data->camera = camera;
	data->mouse = mouse;
	if (!(data->mlx = mlx_init()) ||
		!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF")) ||
		!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	data->camera->x_offset = WIDTH / 2;
	data->camera->y_offset = HEIGHT / 2;
	camera->z_scale = 10;
	camera->projection = 3;
	return (1);
}

int 	main(int ac, char **av)
{
	t_camera	camera;
	t_mouse		mouse;
	t_data		data;
	int			fd;

	if (ac == 1)
		print_error("error: not enough arguments");
	if (ac > 2)
		print_error("error: too many arguments");
	if (!fdf_init(&data, &mouse, &camera))
		print_error("error: initialization");
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !fdf_read_file(fd, &data))
		print_error("error: reading fail");
	fdf_render(&data);
	fdf_control(&data);
	mlx_loop(&data.mlx);
	return (0);
}