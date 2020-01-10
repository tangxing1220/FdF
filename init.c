#include "fdf.h"
#include <errno.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void terminate(char *s)
{
	if(errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

/*
** Initialize t_map elelment
*/
t_map       *map_init(void)
{
    t_map   *map;
    map = (t_map *)ft_memalloc(sizeof(t_map));
    if (map == NULL)
        terminate(ERR_MAP_INIT);
    map->width = 0;
    map->height = 0;
    map->coords_arr = NULL;
    map->colors_arr = NULL;
    map->z_min = FT_INT_MAX;
    map->z_max = FT_INT_MIN;
    map->z_range = 0;
    return (map);
}