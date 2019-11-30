#include "fdf.h"

int		hook_keydown(int key, t_data *mlx)
{
	(void)mlx;
	if (key == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

int		hook_mousedown(int button, int x, int y, t_data *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	mlx->mouse->isdown |= 1 << button;
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_data *mlx)
{
	(void)x;
	(void)y;
	mlx->mouse->isdown &= ~(1 << button);
	return (0);
}

int		hook_mousemove(int x, int y, t_data *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isdown & (1 << 1) && mlx->mouse->isdown & (1 << 2))
	{
		mlx->camera->x_offset += (x - mlx->mouse->lastx);
		mlx->camera->y_offset += (y - mlx->mouse->lasty);
	}
	else if (mlx->mouse->isdown & (1 << 1))
	{
		mlx->camera->alpha += (mlx->mouse->lasty - y) / 200.0f;
		mlx->camera->beta -= (mlx->mouse->lastx - x) / 200.0f;
	}
	else if (mlx->mouse->isdown & (1 << 2))
	{
		mlx->camera->zoom  += (mlx->mouse->lasty - y) / 10.0f + 0.5f;
		if (mlx->camera->zoom  < 1)
			mlx->camera->zoom = 1;
	}
	if (mlx->mouse->isdown)
		fdf_render(mlx);
	return (0);
}

void	fdf_control(t_data *mlx)
{
	mlx_key_hook(mlx->win, hook_keydown, mlx);
	mlx_hook(mlx->win, 4, 0, hook_mousedown, mlx);
	mlx_hook(mlx->win, 5, 0, hook_mouseup, mlx);
	mlx_hook(mlx->win, 6, 0, hook_mousemove, mlx);
}

/*
# define TRUE				1
# define FALSE				0

void	zoom(int key, t_data *fdf)
{
	if (key == NUM_PAD_PLUS ||
		key == MAIN_PAD_PLUS ||
		key == MOUSE_SCROLL_UP)
		fdf->camera->zoom++;
	else if (key == NUM_PAD_MINUS ||
			 key == MAIN_PAD_MINUS ||
			 key == MOUSE_SCROLL_DOWN)
		fdf->camera->zoom--;
	else if (key == MAIN_PAD_0)
	{
		fdf->camera->zoom = FT_MIN(WIDTH / fdf->width / 2, HEIGHT / fdf->height / 2);
		fdf->camera->x_offset = 0;
		fdf->camera->y_offset = 0;
	}
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	fdf_render(fdf);
}

void	move(int key, t_data *fdf)
{
	if (key == ARROW_LEFT || key == MAIN_PAD_D)
		fdf->camera->x_offset -= 10;
	else if (key == ARROW_RIGHT || key == MAIN_PAD_A)
		fdf->camera->x_offset += 10;
	else if (key == ARROW_UP || key == MAIN_PAD_S)
		fdf->camera->y_offset -= 10;
	else if (ARROW_DOWN || key == MAIN_PAD_W)
		fdf->camera->y_offset += 10;
	fdf_render(fdf);
}

void	rotate1(int key, t_data *fdf)
{
	if (key == MAIN_PAD_J)
		fdf->camera->alpha -= 0.05;
	else if (key == MAIN_PAD_U)
		fdf->camera->alpha += 0.05;
	else if (key == MAIN_PAD_K)
		fdf->camera->beta -= 0.05;
	else if (key == MAIN_PAD_I)
		fdf->camera->beta += 0.05;
	else if (key == MAIN_PAD_L)
		fdf->camera->gamma -= 0.05;
	else if (key == MAIN_PAD_O)
		fdf->camera->gamma += 0.05;
	fdf_render(fdf);
}

void	scale(int key, t_data *fdf)
{
	if (key == MAIN_PAD_LESS)
		fdf->camera->z_scale /= 1.1;
	else if (key == MAIN_PAD_MORE)
		fdf->camera->z_scale *= 1.1;
	if (fdf->camera->z_scale < 0.1)
		fdf->camera->z_scale = 0.1;
	else if (fdf->camera->z_scale > fdf->camera->zoom)
		fdf->camera->z_scale = fdf->camera->zoom;
	fdf_render(fdf);
}

void	change_projection(int key, t_data *fdf)
{
	fdf->camera->alpha = 0;
	fdf->camera->beta = 0;
	fdf->camera->gamma = 0;
	if (key == MAIN_PAD_1)
		fdf->camera->projection = 1;
	else if (key == MAIN_PAD_2)
		fdf->camera->alpha = -1.570796;
	else if (key == MAIN_PAD_3)
	{
		fdf->camera->beta = -1.570796;
		fdf->camera->alpha = -1.570796;
	}
	else if (key == MAIN_PAD_4)
		fdf->camera->projection = 0;
	fdf_render(fdf);
}

int			key_press(int key, void *param)
{
	t_data	*fdf;

	fdf = (t_data*)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS || key == MAIN_PAD_0
		|| key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS)
		zoom(key, fdf);
	else if (key == ARROW_LEFT || key == MAIN_PAD_A
			 || key == ARROW_RIGHT || key == MAIN_PAD_D
			 || key == ARROW_UP || key == MAIN_PAD_W
			 || key == ARROW_DOWN || key == MAIN_PAD_S)
		move(key, fdf);
	else if (key == MAIN_PAD_J || key == MAIN_PAD_U
			 || key == MAIN_PAD_K || key == MAIN_PAD_I
			 || key == MAIN_PAD_L || key == MAIN_PAD_O)
		rotate1(key, fdf);
	else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE)
		scale(key, fdf);
	else if (key == MAIN_PAD_1 || key == NUM_PAD_1
			 || key == MAIN_PAD_2 || key == NUM_PAD_2
			 || key == MAIN_PAD_3 || key == NUM_PAD_3
			 || key == MAIN_PAD_4 || key == NUM_PAD_4)
		change_projection(key, fdf);
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_data	*fdf;

	(void)x;
	(void)y;
	fdf = (t_data *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, fdf);
	else if (button == MOUSE_LEFT_BUTTON)
		fdf->mouse->isdown = TRUE;
	return (0);
}

int			mouse_release(int button, int x, int y, void *param)
{
	t_data	*fdf;

	(void)x;
	(void)y;
	(void)button;
	fdf = (t_data *)param;
	fdf->mouse->isdown = FALSE;
	return (0);
}

int			mouse_m(int x, int y, void *param)
{
	t_data	*fdf;

	fdf = (t_data *)param;
	fdf->mouse->lastx = fdf->mouse->x;
	fdf->mouse->lasty = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->isdown)
	{
		fdf->camera->beta += (x - fdf->mouse->lastx) * 0.002;
		fdf->camera->alpha += (y - fdf->mouse->lasty) * 0.002;
		fdf_render(fdf);
	}
	return (0);
}

int			close_win(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	fdf_control(t_data *fdf)
{
	mlx_hook(fdf->win, 2, 0, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_m, fdf);
}*/