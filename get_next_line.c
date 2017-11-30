/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <jjauzion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:23:51 by jjauzion          #+#    #+#             */
/*   Updated: 2017/11/30 21:10:19 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		ft_flush(char **dst, char **buff)
{
	int		index;
	
	index = 0;
	while (**buff && **buff != '\n')
	{
		(*dst)[index] = **buff;
		(*buff)++;
		index++;
	}
	(*dst)[index] = '\0';
ft_putstr("dst = |>|");
ft_putstr(*dst);
ft_putendl("|<|");
	if (**buff == '\n')
	{
		(*buff)++;
		return (-1);
	}
	return (index);
}

int		get_next_line(const int fd, char **line)
{
	static char	tmp[BUFF_SIZE + 1] = "";
	static char	*ptr = tmp;
	size_t		ret;
	int			i;

ft_putstr("buff malloc = ");
ft_putendl(ft_itoa(BUFF_SIZE + ft_strlen(tmp) - (ptr - tmp) + 1));
	if (!((*line) = (char *)malloc(sizeof(char) * (BUFF_SIZE + ft_strlen(tmp) - (ptr - tmp) + 1))))
		return (-1);
ft_putstr("tmp = |>|");
ft_putstr(tmp);
ft_putendl("|<|");
ft_putstr("ptr = |>|");
ft_putstr(ptr);
ft_putendl("|<|");
	if ((i = ft_flush(line, &ptr)) < 0)
	{
ft_putstr("line = |>|");
ft_putstr(*line);
ft_putendl("|<|");
		return (1);
	}
	ret = 1;
	ptr = tmp;
	while (ret)
	{
		ret = read(fd, tmp, BUFF_SIZE);
		if (ret == 0)
			return (0);
		tmp[ret] = '\0';
		while (*ptr && *ptr != '\n')
		{
			(*line)[i] = *ptr;
			i++;
			ptr++;
		}
		(*line)[i] = '\0';
		if (*ptr == '\n')
		{
			ptr++;
			ret = 0;
		}
		else
			ft_strext(line, ft_strlen(*line), BUFF_SIZE + 1);
	}
	return (1);
}
