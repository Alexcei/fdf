#include "fdf.h"

void	rotate1(t_dot *dot, double alpha, double beta)
{
	double		x;
	double		y;

	x = dot->x;
	y = dot->y;
	dot->x = cos(beta) * x + sin(beta) * dot->z;
	dot->z = -sin(beta) * x + cos(beta) * dot->z;
	dot->y = cos(alpha) * y - sin(alpha) * dot->z;
	dot->z = sin(alpha) * y + cos(alpha) * dot->z;
}

t_dot		projection(t_dot dot, t_data *data)
{
	dot.x -= (data->width - 1) / 2;
	dot.y -= (data->height - 1) / 2;
	dot.z -= (data->z_min + data->z_max) / 2;
	if (data->camera->projection == 0)
		rotate1(&dot, 0, 0);
	else if (data->camera->projection == 1)
		rotate1(&dot, 1.570796, 0);
	else if (data->camera->projection == 2)
		rotate1(&dot, 0, 1.570796);
	else if (data->camera->projection == 3)
		{
			dot.x = (dot.x - dot.y) * cos(1);
			dot.y = (dot.x + dot.y) * sin(1.1) - dot.z;
		}
	else
		rotate1(&dot, data->camera->alpha, data->camera->beta);
	dot.x *= data->camera->zoom;
	dot.y *= data->camera->zoom;
	dot.x += data->camera->x_offset;
	dot.y += data->camera->y_offset;
	return (dot);
}

/*
void	rotate1(t_dot *dot, double alpha, double beta)
{
	dot->x = (dot->x - dot->y) * cos(alpha + beta);
	dot->y = (dot->x + dot->y) * sin(alpha - beta) - dot->z;
}*/