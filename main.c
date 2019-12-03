/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:28:03 by bpole             #+#    #+#             */
/*   Updated: 2019/12/03 22:59:23 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		fdf_close(void *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}

static int		fdf_init(t_data *data, t_camera *camera)
{
	ft_bzero(camera, sizeof(t_camera));
	ft_bzero(data, sizeof(t_data));
	data->camera = camera;
	if (!(data->mlx = mlx_init()) ||
			!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF")) ||
			!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	data->camera->x_offset = WIDTH / 2;
	data->camera->y_offset = HEIGHT / 2;
	camera->view_selection = 4;
	data->camera->color_selection = 2;
	return (1);
}

int				main(int ac, char **av)
{
	t_camera	camera;
	t_data		data;
	int			fd;

	if (ac == 1)
		print_error("error: not enough arguments");
	if (ac > 2)
		print_error("error: too many arguments");
	if (!fdf_init(&data, &camera))
		print_error("error: initialization");
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !fdf_read_file(fd, &data))
		print_error("error: reading fail");
	fdf_render(&data);
	mlx_hook(data.win, 17, 0, fdf_close, &data);
	mlx_key_hook(data.win, fdf_hook_keydown, &data);
	mlx_loop(&data.mlx);
	return (0);
}
