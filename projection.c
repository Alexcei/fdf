#include "fdf.h"

static void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.46373398);
	*y = -z + (previous_x + previous_y) * sin(0.46373398);
}

t_dot		projection(t_dot point, t_data *fdf)
{
	point.x *= fdf->camera->zoom;
	point.y *= fdf->camera->zoom;
	point.z *= fdf->camera->zoom / fdf->camera->z_divider;
	point.x -= (fdf->width * fdf->camera->zoom) / 2;
	point.y -= (fdf->height * fdf->camera->zoom) / 2;
	rotate_x(&point.y, &point.z, fdf->camera->alpha);
	rotate_y(&point.x, &point.z, fdf->camera->beta);
	rotate_z(&point.x, &point.y, fdf->camera->gamma);
	if (fdf->camera->projection == ISO)
		iso(&point.x, &point.y, point.z);
	point.x += WIDTH / 2 + fdf->camera->x_offset;
	point.y += (HEIGHT + fdf->height * fdf->camera->zoom) / 2
			   + fdf->camera->y_offset;
	return (point);
}