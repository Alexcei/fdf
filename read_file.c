#include "fdf.h"

static void		creat_arr(t_data *data, char *coords)
{
	char 		**arr;
	int 		i;

	i = 0;
	arr = ft_strsplit(coords, ' ');
	data->map->dot = (t_dot*)ft_memalloc(sizeof(t_dot) * data->map->size);
	while (arr[i])
	{
		data->map->dot[i].x = i % data->map->width;
		data->map->dot[i].y = i / data->map->width;
		data->map->dot[i].z = ft_atoi(arr[i]);
		i++;
	}
	ft_free_char_arr(&arr);
	ft_strdel(&coords);
}

static void		ft_strjoin_and_free(char **mutable, char *str)
{
	char 		*tmp;

	tmp = *mutable;
	*mutable = ft_strjoin(*mutable, str);
	ft_strdel(&tmp);
}

int 			fdf_read_file(int fd, t_data *data)
{
	char 		*line;
	char 		*coords;

	line = NULL;
	coords = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		if (!line)
			return (0);
		if (!data->map->width)
			data->map->width = ft_word_count(line, ' ');
		if (!data->map->width || data->map->width != ft_word_count(line, ' '))
			return (0);
		ft_strjoin_and_free(&coords, line);
		ft_strjoin_and_free(&coords, " ");
		data->map->height++;
		ft_strdel(&line);
	}
	data->map->size = data->map->width * data->map->height;
	data->camera->zoom = FT_MIN(WIDTH / data->map->width / 2, HEIGHT / data->map->height / 2);
	creat_arr(data, coords);
	return (1);
}