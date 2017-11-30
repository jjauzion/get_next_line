/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <jjauzion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:23:51 by jjauzion          #+#    #+#             */
/*   Updated: 2017/11/30 19:15:13 by jjauzion         ###   ########.fr       */
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
ft_putendl("In--");
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
ft_putendl("JESUISLA");
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

	if (!((*line) = (char *)malloc(sizeof(char) * (BUFF_SIZE + ptr - tmp + 1))))
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
		else if (ret == 0)
			return (0);
		else
			ft_strext(line, ft_strlen(*line), BUFF_SIZE + 1);
	}
	return (1);
}
