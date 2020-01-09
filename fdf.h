#ifndef FDF_H
# define FDF_H

typedef struct s_map
{
    int width;
    int height;
    int *coords_arr;
    int *colors_arr;
    int z_min;
    int z_max;
    int z_range;
}               t_map;

#endif