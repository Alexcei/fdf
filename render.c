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

void	render_map(t_data *data)
{
	t_dot	dot;
	int 	i;

	i = 0;
	while (i < data->map->size)
	{
		dot = projection(data->map->dot[i], data);
		if ((i + 1) % data->map->width != 0)
			render_line(dot, projection(data->map->dot[i + 1], data), data);
		if (i / data->map->width != data->map->height - 1)
			render_line(dot, projection(data->map->dot[i + data->map->width], data), data);
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

/*
 * # define MAX(a, b) (a > b ? a : b)
# define MOD(a) (a < 0 ? -a : a)

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.9);
	*y = (*x + *y) * sin(1.1) - z;
}

void	bresenham(int x, int y, int x1, int y1, t_data *data)
{
	float 	x_step;
	float 	y_step;
	int 	max;
	int 	z;
	int 	z1;

	z = ((data->map->dot)[y * x]).z;
	z1 = ((data->map->dot)[y1 * x1]).z;

	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;

	data->color = (z || z1) ? 0xe80c0c : 0xffffff;

	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);

	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;

	x_step = x1 - x;
	y_step = y1 - y;

	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx, data->win, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	render_map(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (x < data->map->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->map->height - 1)
				bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
 */


/*
t_dot	rotate(t_dot p, t_camera *r)
{
	t_dot	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(r->beta) * x + sin(r->beta) * z;
	v.z = -sin(r->beta) * x + cos(r->beta) * z;
	y = p.y;
	z = v.z;
	v.y = cos(r->alpha) * y - sin(r->alpha) * z;
	v.z = sin(r->alpha) * y + cos(r->alpha) * z;
	v.color = p.color;
	return (v);
}

t_dot		projection_dot(t_dot v, t_data *data)
{
	v.x -= (double)(data->map->width - 1) / 2.0f;
	v.y -= (double)(data->map->height - 1) / 2.0f;
	v.z -= (double)(data->map->z_min + data->map->z_max) / 2.0f;
	v = rotate(v, data->camera);
	v.x *= data->camera->zoom;
	v.y *= data->camera->zoom;
	v.x += data->camera->x_offset;
	v.y += data->camera->y_offset;
	return (v);
}

void	render_map(t_data *data)
{
	t_dot	dot;
	int 	i;

	i = 0;
	while (i < data->map->size)
	{
		dot = projection_dot((data->map->dot)[i], data);
		if ((i + 1) % data->map->width != 0)
			line(data->mlx, dot, projection_dot((data->map->dot)[i + 1], data));
		if (i / data->map->width != data->map->height - 1)
			line(data->mlx, dot, projection_dot((data->map->dot)[i + data->map->width], data));
		i++;
	}
}*/