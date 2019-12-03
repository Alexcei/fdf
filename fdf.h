/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:27:41 by bpole             #+#    #+#             */
/*   Updated: 2019/12/03 01:57:08 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf/ft_printf.h"
# include <mlx.h>
# include <math.h>

# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0xA0B0C0

# define HEIGHT			600
# define WIDTH			900
# define SIZE 			HEIGHT * WIDTH

# define FT_MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define MOD(a) (a < 0 ? -a : a)

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_C			8
# define MAIN_PAD_V			9
# define MAIN_PAD_P			35

typedef	enum
{
	FRONT,
	TOP,
	SIDE,
	ISO,
	FREE
}	t_projection;

typedef struct		s_camera
{
	int				zoom;
	double			alpha;
	double			beta;
	double			x_offset;
	double			y_offset;
	int				polygon;
	int				color_selection;
	int				view_selection;
}					t_camera;

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_dot;

typedef struct		s_data
{
	t_camera		*camera;
	t_dot			*dot;
	int				width;
	int				height;
	int				size;
	int				z_min;
	int				z_max;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_data;

/*
**					bresenham.c
*/
void				render_line(t_dot a, t_dot b, t_data *data);
void				render_plane(t_dot a, t_dot b, t_dot c, t_data *data);

/*
**					control.c
*/
int					fdf_hook_keydown(int key, t_data *data);

/*
**					projection.c
*/
t_dot				transformations(t_dot point, t_data *data);

/*
**					read_file.c
*/
int					fdf_read_file(int fd, t_data *data);

/*
**					render.c
*/
void				fdf_render(t_data *data);

/*
**					utils.c
*/
void				print_error(char *message);
void				ft_free_char_arr(char ***arr);
int					ft_word_count(char const *str, char c);
int					ft_atoi_base(const char *str, int base);

#endif
