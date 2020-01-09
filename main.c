/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:41:34 by xtang             #+#    #+#             */
/*   Updated: 2020/01/09 16:09:03 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Terminate execution and display error message
*/
#include "error_message.h"
#include "fdf.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

void terminate(char *s)
{
	if(errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}


int main(int argc, char **argv)
{
	int fd;
	t_map	*map;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate(ERR_MAP);
		map = map_init();






	}
	terminate(ERR_USAGE);
	return (0);
}

