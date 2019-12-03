/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 01:29:49 by bpole             #+#    #+#             */
/*   Updated: 2019/12/03 01:49:45 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			print_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

void			ft_free_char_arr(char ***arr)
{
	int			i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			ft_strdel(&((*arr)[i++]));
		free(*arr);
		*arr = NULL;
	}
}

int				ft_word_count(char const *str, char c)
{
	int			tr;
	int			res;

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

static int		nbr_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10))
			|| (c >= 'a' && c <= ('a' + base - 10)));
}

int				ft_atoi_base(const char *str, int base)
{
	size_t		i;
	int			sing;
	long long	res;

	if (!str[0] || (base < 2 || base > 16))
		return (0);
	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	sing = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && nbr_inbase(str[i], base))
	{
		if (str[i] >= 'A' && 'F' >= str[i])
			res = (res * base) + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && 'f' >= str[i])
			res = (res * base) + (str[i] - 'a' + 10);
		else
			res = (res * base) + (str[i] - '0');
		i += 1;
	}
	return (res * sing);
}
