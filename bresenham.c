#include "fdf.h"

double	percent(int start, int end, int current)
{
	double		placement;
	double		distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static void			plot(t_dot point, int color, t_data *fdf)
{
	int		i;

	if (0 < point.x && point.x < WIDTH && 0 < point.y && point.y < HEIGHT)
	{
		i = (point.x * fdf->bits_per_pixel / 8) + (point.y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

int get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int get_color(t_dot current, t_dot start, t_dot end, t_dot delta)
{
	int     red;
	int     green;
	int     blue;
	double  percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void			render_line(t_dot a, t_dot b, t_data *fdf)
{
	t_dot		delta;
	t_dot		sign;
	int			error[2];
	t_dot		current;

	delta.x = FT_ABS(b.x - a.x);
	delta.y = FT_ABS(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	current = a;
	while (current.x != b.x || current.y != b.y)
	{
		plot(current, get_color(current, a, b, delta), fdf);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			current.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			current.y += sign.y;
		}
	}
}