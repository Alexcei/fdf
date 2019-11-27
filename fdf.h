#ifndef FDF_H
# define FDF_H

#include "ft_printf/ft_printf.h"
#include <mlx.h>
#include <math.h>

# define HEIGHT			1080
# define WIDTH			1920
# define SIZE 			HEIGHT * WIDTH
# define MENU_WIDTH		250
# define BACKGROUND			0xA0B0C0
# define MENU_BACKGROUND	0xC0B0A0

typedef				enum
{
					false,
					true
}					t_bool;

typedef 			enum
{
					ISO,
					PARALLEL_FRONT,
					PARALLEL_SIDE,
					PARALLEL_ABOVE
}					t_projection;

typedef struct		s_camera
{
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	float			z_divider;
	int				x_offset;
	int				y_offset;
	t_projection	projection;
}					t_camera;

typedef struct		s_map
{
	int				width;
	int				height;
	int				z_min;
	int				z_max;
	int				*arr_z;
	int 			*arr_c;
}					t_map;

typedef struct		s_mouse
{
	char			isdown;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;

typedef struct		s_data
{
	t_camera		*camera;
	t_map			*map;
	t_mouse			*mouse;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_data;

/*
**					read_file.c
*/
int 				fdf_read_file(int fd, t_data *data);

/*
**					utils.c
*/
void				print_error(char *message);
void				ft_free_char_arr(char ***arr);
size_t				ft_word_count(char const *str, char c);

#endif