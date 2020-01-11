#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

void stack_to_arrays(t_coord_val **coords_stack, t_map *map)
{
    t_coord_val *coord;
    ssize_t     i;
    size_t      arr_size;

    arr_size = map->width * map-> height * sizeof(int);
    if (!(map->coords_arr = (int *)ft_memalloc(arr_size)))
        terminate(ERR_CONV_TO_ARR);
    if (!(map->colors_arr = (int *)ft_memalloc(arr_size)))
        terminate(ERR_CONV_TO_ARR);
    i = map->width * map->height -1;

    while ((coord = pop(coords_stack)) && i >= 0)
    {
        map->coords_arr[i] = coord->z;
        map->colors_arr[i] = coord->color;
        if (coord->z > map->z_max)
            map->z_max = coord->z;
        if (coord->z < map->z_min)
            map->z_min = coord->z;
        i--;
        free(coord);
    }
    map->z_range = map->z_max - map->z_min;
}