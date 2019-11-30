#include "fdf.h"

static void			paint_point(int x, int y, t_data *data)
{
	int		i;

	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
		((int*)(data->data_addr))[i] = COLOR_FDF;
}

void			render_line(t_dot a, t_dot b, t_data *data)
{
	double 	x_step;
	double 	y_step;
	int 	max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		paint_point((int)a.x, (int)a.y, data);
		a.x += x_step;
		a.y += y_step;
	}
}