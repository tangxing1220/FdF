#ifndef FDF_H
# define FDF_H

# define HEIGHT 1080
# define WIDTH  1920
# define MENU_WIDTH  250

#include "error_message.h"



typedef enum
{
    false,
    true
}   t_bool;

typedef enum
{
    ISO,
    PARALLEL
}   t_projection;

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

typedef struct s_coord_val
{
    int z;
    int color;
    struct s_coord_val *next;
}               t_coord_val;

typedef struct s_camera
{
    t_projection    porjection;
    int             zoom;
    double          alpha;
    double          beta;
    double          gamma;
    float           z_divisor;
    int             x_offset;
    int             y_offset;
}                   t_camera;

typedef struct s_mouse
{
    char    is_pressed;
    int     x;
    int     y;
    int     previous_x;
    int     previous_y;
}               t_mouse;

typedef struct s_fdf
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *data_addr;
    int         bits_per_pixel;
    int         size_line;
    int         endian;
    t_camera    *camera;
    t_map       *map;
    t_mouse     *mouse;
}               t_fdf;

void terminate(char *s);
t_map       *map_init(void);
int         read_map(const int fd, t_coord_val **coords_stack, t_map *map);
t_fdf       *fdf_init(t_map *map);
void        stack_to_arrays(t_coord_val **coords_stack, t_map *map);
t_coord_val     *pop(t_coord_val **coords_stack);
void            push(t_coord_val **coords_stack, t_coord_val *new);
t_bool      ft_isnumber(char *str, int base);
int         ft_atoi_base(const char *str, int base);

#endif