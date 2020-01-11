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
#include "fdf.h"
#include <fcntl.h>




int main(int argc, char **argv)
{
	int fd;
	t_map	*map;
	t_coord_val *coords_stack;
	t_fdf	*fdf;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate(ERR_MAP);
		map = map_init();
		if (read_map(fd, &coords_stack, map) == -1)
			terminate(ERR_MAP_READING);
		fdf = fdf_init(map);
		stack_to_arrays(&coords_stack, map);






	}
	terminate(ERR_USAGE);
	return (0);
}

