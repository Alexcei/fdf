/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:27:31 by bpole             #+#    #+#             */
/*   Updated: 2019/12/03 01:46:25 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		color_up(t_data *data)
{
	if (data->camera->color_selection < 3)
		data->camera->color_selection++;
	else
		data->camera->color_selection = 0;
}

static void		view_up(t_data *data)
{
	if (data->camera->view_selection < 4)
		data->camera->view_selection++;
	else
		data->camera->view_selection = 0;
}

static void		polygon_up(t_data *data)
{
	if (!data->camera->polygon)
		data->camera->polygon++;
	else
		data->camera->polygon--;
}

static void		zoom_down(t_data *data)
{
	data->camera->zoom -= 1;
	if (data->camera->zoom < 1)
		data->camera->zoom = 1;
}

int				fdf_hook_keydown(int key, t_data *data)
{
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_C)
		color_up(data);
	if (key == MAIN_PAD_V)
		view_up(data);
	if (key == MAIN_PAD_P)
		polygon_up(data);
	if (key == NUM_PAD_MINUS)
		zoom_down(data);
	if (key == NUM_PAD_PLUS)
		data->camera->zoom += 1;
	if (key == ARROW_UP)
		data->camera->alpha += 0.1f;
	if (key == ARROW_DOWN)
		data->camera->alpha -= 0.1f;
	if (key == ARROW_LEFT)
		data->camera->beta -= 0.1f;
	if (key == ARROW_RIGHT)
		data->camera->beta += 0.1f;
	fdf_render(data);
	return (0);
}
