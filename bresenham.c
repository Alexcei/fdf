#include "fdf.h"

# define NEW_LIGHT(a, b, per)	((int)((1 - per) * a + per * b))
# define GET_RED(color)		((color >> 16) & 0xFF)
# define GET_GREEN(color)	((color >> 8) & 0xFF)
# define GET_BLUE(color)	(color & 0xFF)
# define RGB(r, g, b)	    ((r << 16) | (g << 8) | b)

static double	percentage(int start, int end, int current)
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

int				get_color(t_dot current, t_dot a, t_dot b, t_dot delta)
{
	double		percent;

	if (current.color == b.color)
		return (current.color);
	if (delta.x > delta.y)
		percent = percentage(a.x, b.x, current.x);
	else
		percent = percentage(a.y, b.y, current.y);
	return (RGB(NEW_LIGHT(GET_RED(a.color), GET_RED(b.color), percent),
				NEW_LIGHT(GET_GREEN(a.color), GET_GREEN(b.color), percent),
				NEW_LIGHT(GET_BLUE(a.color), GET_BLUE(b.color), percent)));
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