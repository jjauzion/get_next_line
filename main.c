/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <jjauzion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:48:29 by jjauzion          #+#    #+#             */
/*   Updated: 2017/12/06 15:09:23 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: one argument required with the name of the file to be read", 2);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putendl_fd("open file error", 2);
		return (1);
	}
	ret = 1;
	while (ret == 1)
	{
		ft_putstr(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		ret = get_next_line(fd, &line);
		ft_putstr("ret= ");
		ft_putnbr(ret);
		ft_putendl("");
		ft_putstr("Line = |>|");
		ft_putstr(line);
		ft_putendl("|<|");
		ft_strdel(&line);
		ft_putendl("<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	}
	return(0);
}	
