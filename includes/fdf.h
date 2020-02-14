/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xtang <xtang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:23:16 by xtang             #+#    #+#             */
/*   Updated: 2020/02/14 16:09:19 by xtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250

# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))
# define FT_MAX(A, B) (((A) > (B)) ? (A) : (B))

# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))

# define FT_ULONG_MAX	((unsigned long)(~0L))
# define FT_LONG_MAX	((long)(FT_ULONG_MAX >> 1))
# define FT_LONG_MIN	((long)(~FT_LONG_MAX))

# define FT_UINT_MAX	((unsigned)(~0L))
# define FT_INT_MAX		((int)(FT_UINT_MAX >> 1))
# define FT_INT_MIN		((int)(~FT_INT_MAX))

typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

typedef struct			s_coord_val
{
	int					z;
	int					color;
	struct s_coord_val	*next;
}						t_coord_val;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_camera
{
	t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					x_offset;
	int					y_offset;
}						t_camera;

typedef struct			s_map
{
	int					width;
	int					height;
	int					*coords_arr;
	int					*colors_arr;
	int					z_min;
	int					z_max;
	int					z_range;
}						t_map;

typedef struct			s_mouse
{
	char				is_pressed;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;

typedef struct			s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_camera			*camera;
	t_map				*map;
	t_mouse				*mouse;
}						t_fdf;

int						read_map(const int fd,
								t_coord_val **coords_stack,
								t_map *map);

void					push(t_coord_val **coords_stack,
							t_coord_val *new);

t_coord_val				*pop(t_coord_val **coords_stack);

t_map					*map_init(void);

t_fdf					*fdf_init(t_map *map);

t_camera				*camera_init(t_fdf *fdf);

void					stack_to_arrays(t_coord_val **coords_stack,
										t_map *map);

void					draw(t_map *map,
							t_fdf *fdf);

int						get_default_color(int z,
										t_map *map);

int						get_light(int start,
								int end,
								double percentage);

int						get_color(t_point current,
								t_point start,
								t_point end,
								t_point delta);

t_point					project(t_point p,
								t_fdf *fdf);

void					print_menu(t_fdf *fdf);

int						ft_close(void *param);

void					setup_controls(t_fdf *fdf);

int						key_press(int key,
								void *param);

int						mouse_press(int button,
									int x,
									int y,
									void *param);

int						mouse_release(int button,
									int x,
									int y,
									void *param);

int						mouse_move(int x,
								int y,
								void *param);

void					zoom(int key,
							t_fdf *fdf);

void					move(int key,
							t_fdf *fdf);

void					rotate(int key,
							t_fdf *fdf);

void					flatten(int key,
								t_fdf *fdf);

void					change_projection(int key,
										t_fdf *fdf);

int						ft_isnumber(char *str, int base);

int						ft_atoi_base(const char *str, int base);

double					percent(int start, int end, int current);

void					terminate(char *s);

int						get_index(int x, int y, int width);

t_point					new_point(int x, int y, t_map *map);

#endif
