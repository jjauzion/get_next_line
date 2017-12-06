/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <jjauzion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:23:51 by jjauzion          #+#    #+#             */
/*   Updated: 2017/12/06 14:56:54 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int		ft_flush(char *dst, t_file *f)
{
	int		i;

	i = ft_strlen(dst);
/*ft_putendl("---------------------------------");
ft_putstr("buff = |");
ft_putstr(f->buff);
ft_putendl("|");
ft_putstr("dst = |");
ft_putstr(dst);
ft_putendl("|");
ft_putstr("index = ");
ft_putendl(ft_itoa(f->index));
ft_putstr("ret = ");
ft_putendl(ft_itoa(f->ret));
ft_putstr("i = ");
ft_putendl(ft_itoa(i));
ft_putendl("---------------------------------");
*/	while (f->index < f->ret && f->buff[f->index] != '\n')
	{
		dst[i] = f->buff[f->index];
		f->index++;
		i++;
	}
	dst[i] = '\0';
/*ft_putendl("+++++++++++++++++++++++++++++++++");
ft_putstr("buff = |");
ft_putstr(f->buff);
ft_putendl("|");
ft_putstr("dst = |");
ft_putstr(dst);
ft_putendl("|");
ft_putstr("index = ");
ft_putendl(ft_itoa(f->index));
ft_putstr("ret = ");
ft_putendl(ft_itoa(f->ret));
ft_putstr("i = ");
ft_putendl(ft_itoa(i));
ft_putendl("+++++++++++++++++++++++++++++++++");
*/	if (f->index >= f->ret)
		return (0);
	f->index++;
	return (1);
}

int		ft_read(char **str, t_file *f)
{
	while (1)
	{
		f->index = 0;
		if ((f->ret = read(f->fd, f->buff, BUFF_SIZE)) < 0)
			return (ERROR);
		if (f->ret == 0)
			return (EOFF);
		if (ft_flush(*str, f))
			return (EOL);
		*str = ft_strext(str, ft_strlen(*str), BUFF_SIZE + 1);
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

int		get_next_line(const int fd, char **line)
{
	static t_file	*file_lst = NULL;
	t_file			*f;
	char			*str;
	int				status;

	f = ft_file_lst(fd, &file_lst);
	if (!(str = (char *)malloc(sizeof(char) * (BUFF_SIZE + ft_strlen(f->buff) - f->index + 1))))
				return (ERROR);
	str[0] = '\0';
	if (ft_flush(str, f))
	{
		*line = ft_strdup(str);
		ft_strdel(&str);
		return (EOL);
	}
	if ((status = ft_read(&str, f)) == ERROR)
		return (ERROR);
	if (*str == '\0' && status == EOFF)
	{	
		ft_strdel(&str);
		return (EOFF);
	}
	*line = ft_strdup(str);
	ft_strdel(&str);
	return (EOL);
}
