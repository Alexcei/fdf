#include "fdf.h"

void		print_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

void		ft_free_char_arr(char ***arr)
{
	int		i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			ft_strdel(&((*arr)[i++]));
		free(*arr);
		*arr = NULL;
	}
}

int			ft_word_count(char const *str, char c)
{
	int		tr;
	int		res;

	tr = 0;
	res = 0;
	while (*str)
	{
		if (*str != c && tr == 0)
			res++;
		tr = (*str++ != c ? 1 : 0);
	}
	return (res);
}