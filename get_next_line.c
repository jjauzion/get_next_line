/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <jjauzion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:23:51 by jjauzion          #+#    #+#             */
/*   Updated: 2017/12/06 17:39:59 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		ft_flush(char *dst, t_file *f, int *len)
{
	while (f->index < f->ret && f->buff[f->index] != '\n')
	{
		dst[*len] = f->buff[f->index];
		f->index++;
		(*len)++;
	}
	dst[*len] = '\0';
	if (f->index >= f->ret)
		return (0);
	f->index++;
	return (1);
}

int		ft_read(char **str, t_file *f, int *len)
{
	while (1)
	{
		f->index = 0;
		if ((f->ret = read(f->fd, f->buff, BUFF_SIZE)) < 0)
			return (ERROR);
		if (f->ret == 0)
		{
			if (*str == '\0')
				ft_strdel(str);
			return (EOFF);
		}
		if (ft_flush(*str, f, len))
			return (EOL);
		*str = ft_strext(str, *len, BUFF_SIZE + 1);
	}
}

t_file	*ft_file_lst(const int fd, t_file **f)
{
	t_file	*elm;

	elm = *f;
	while (elm)
	{
		if (elm->fd == fd)
			return (elm);
		elm = elm->next;
	}
	if (!(elm = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (!(elm->buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	elm->fd = fd;
	elm->ret = 0;
	elm->index = 0;
	elm->next = *f;
	*f = elm;
	return (elm);
}

void	*ft_memdup(const void *src, size_t n)
{
	void	*dst;

	if (!(dst = ft_memalloc(n + 1)))
		return (NULL);
	dst = ft_memcpy(dst, src, n + 1);
	return (dst);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*file_lst = NULL;
	t_file			*f;
	char			*str;
	int				status;
	int				len;

	len = 0;
	f = ft_file_lst(fd, &file_lst);
	str = ft_strnew(BUFF_SIZE + ft_strlen(f->buff) - f->index + 1);
	if (!f || !str)
		return (ERROR);
	if (ft_flush(str, f, &len))
	{
		*line = ft_memdup(str, len);
		ft_strdel(&str);
		return (EOL);
	}
	if ((status = ft_read(&str, f, &len)) == ERROR)
		return (ERROR);
	if (*str == '\0' && status == EOFF)
		return (EOFF);
	*line = ft_memdup(str, len);
	ft_strdel(&str);
	return (EOL);
}
