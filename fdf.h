#ifndef FDF_H
# define FDF_H

#include "ft_printf/ft_printf.h"
#include <mlx.h>
#include <math.h>

# define HEIGHT			1080
# define WIDTH			1920
# define SIZE 			HEIGHT * WIDTH
# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0xA0B0C0

# define FT_MIN(a, b)		(((a) < (b)) ? (a) : (b))

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

typedef struct		s_dot
{
	int				x;
	int 			y;
	int 			z;
	int 			color;
}					t_dot;

typedef struct		s_map
{
	int				width;
	int				height;
	int 			size;
	int				z_min;
	int				z_max;
	t_dot			*dot;
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

	int 	zoom;
	int 	color;
	int		shift_x;
	int     shift_y;
}					t_data;

/*
**					bresenham.c
*/
void				render_line(t_dot a, t_dot b, t_data *data);

/*
**					control.c
*/
void				fdf_control(t_data *fdf);

/*
**					projection.c
*/
t_dot				projection(t_dot point, t_data *data);

/*
**					read_file.c
*/
int 				fdf_read_file(int fd, t_data *data);

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

# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2
# define MOUSE_THIRD_BUTTON	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define MOUSE_SCROLL_LEFT	6
# define MOUSE_SCROLL_RIGHT	7

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_1			83
# define NUM_PAD_2			84
# define NUM_PAD_3			85
# define NUM_PAD_4			86
# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_W			13
# define MAIN_PAD_A			0
# define MAIN_PAD_S			1
# define MAIN_PAD_D			2
# define MAIN_PAD_J			38
# define MAIN_PAD_K			40
# define MAIN_PAD_L			37
# define MAIN_PAD_U			32
# define MAIN_PAD_I			34
# define MAIN_PAD_O			31
# define MAIN_PAD_0			29
# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27
# define MAIN_PAD_LESS		43
# define MAIN_PAD_MORE		47

#endif