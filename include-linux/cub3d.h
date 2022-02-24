/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:31:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/24 10:12:07 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../Libft/libft.h"
# include <stdbool.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define MINIMAP_WIDTH	WINDOW_WIDTH
# define MINIMAP_HEIGHT	WINDOW_HEIGHT
# define FOV_ANGLE		1.0471975512
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
# define PI				3.14159265358979323846	
# define PI_2			1.57079632679489661923
# define PI_4			0.78539816339744830962
# define TWO_PI     (6.28318530717958647692528676655900576)
# define TILE_SIZE 		64

typedef struct s_player
{
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	pa;
}				t_player;

typedef struct s_key
{
	int w;
	int a;
	int s;
	int d;
	int l;
	int r;
} 			t_key;

typedef struct s_map
{
	char	**mapdata;
	int		x;
	int		y;
}				t_map;

typedef struct s_p
{
	int	x;
	int	y;
}				t_p;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray_util
{
	int		found_wall_hit;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
	int 	facing_down;
	int		facing_up;
	int		facing_right;
	int		facing_left;
}				t_ray_util;

typedef struct s_ray
{
	double		hitx;
	double		hity;
	double		dist;
	double		ra;
	int			hit_v;
	int 		facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
	int			wall_dir;
} t_ray;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		width;
	int		height;
	int		endian;
	int		size_line;
	int		bpp;
}				t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_ray		ray;
	t_key 		key;
	t_img 		screen;
	t_img		texture[4];
	int 		f_color;
	int 		c_color;
	t_map		map;
	t_player	player;
	int 		tile_size;
} 				t_vars;

void	put_error(char *str);
void	parse(char *filename, t_vars *vars);
void 	map_wall_check(t_vars *vars);
void	parse_map(t_vars *vars);
void	malloc_mapdata(t_vars *vars);
void	set_tile_size(t_vars *vars);
void	get_map_x_y(int skip_line, char *filename, t_vars *vars);

int		tmp_len(char **tmp);
void	check_extension(char *filename);
void 	split_free(char **str);

void	set_map(int skip_line, char *filename, t_vars *vars);
void 	get_map_x_y(int skip_line, char *filename, t_vars *vars);

void 	draw_minimap(t_vars *vars);
void 	draw_player(t_vars *vars);

int		keyrelease(int keycode, t_vars *vars);
int		keypress(int keycode, t_vars *vars);
void	move_up(t_vars *vars);
void	move_down(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);
void	rotate_left(t_vars *vars);
void 	rotate_right(t_vars *vars);
int		is_wall(t_vars *vars, double new_px, double new_py);
int		check_edge(t_vars *vars, int new_mapx, int new_mapy);


int		close_window(void);
void	draw(t_vars *vars);

void	draw_image_test(t_vars *vars);
void	ray_draw(t_vars *data);
void	draw_line(t_vars *vars, t_p start, t_p end);
void	draw_pixel(t_img *img, int x, int y, int color);

#endif