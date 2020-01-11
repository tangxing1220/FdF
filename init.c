#include "fdf.h"
#include <errno.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include "error_message.h"
#include "mlx.h"

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

/*
** Initialize t_fdf element
*/

t_fdf   *fdf_init(t_map *map)
{
    t_fdf   *fdf;

    if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
        terminate(ERR_FDF_INIT);
    if (!(fdf->mlx = mlx_init()))
        terminate(ERR_FDF_INIT);
    if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF")))
        terminate(ERR_FDF_INIT);
    if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
        terminate(ERR_FDF_INIT);
    fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), 
                                        &(fdf->size_line), &(fdf->endian));
    fdf->map = map;
    if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
        terminate(ERR_FDF_INIT);
    return (fdf);
}