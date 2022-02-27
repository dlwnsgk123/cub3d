/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:31:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/27 09:47:39 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../Libft/libft.h"

# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_ESC			53
# define WINDOW_WIDTH		1280
# define WINDOW_HEIGHT		720
# define FOV_ANGLE			1.0471975512
# define PI					3.14159265358979323846	
# define PI_2				1.57079632679489661923
# define PI_4				0.78539816339744830962
# define TWO_PI 			6.28318530717958647692
# define TILE_SIZE 			64
# define NO					0
# define SO					1
# define EA					2
# define WE					3

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
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}				t_key;

typedef struct s_map
{
	char	**mapdata;
	int		x;
	int		y;
}				t_map;

typedef struct s_render
{
	int		width;
	int		wall_start;
	int		wall_end;
	int		y;
	double	wall_height;
}	t_render;

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
}				t_ray_util;

typedef struct s_ray
{
	double		hitx;
	double		hity;
	double		dist;
	double		ra;
	int			hit_v;
	int			facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
	int			wall_dir;
}				t_ray;

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
	t_key		key;
	t_img		screen;
	t_img		texture[4];
	int			f_color;
	int			c_color;
	t_map		map;
	t_player	player;
}				t_vars;

void	put_error(char *str);
void	parse(char *filename, t_vars *vars);
void	map_wall_check(t_vars *vars);
void	parse_map(t_vars *vars);
void	malloc_mapdata(t_vars *vars);
void	get_map_x_y(int skip_line, char *filename, t_vars *vars);
void	check_multi_map(int skip_line, char *filename);
void	tmp_isnum(char **tmp);

int		tmp_len(char **tmp);
void	check_extension(char *filename);
void	split_free(char **str);

void	set_map(int skip_line, char *filename, t_vars *vars);
void	set_map_x_y(int skip_line, char *filename, t_vars *vars);

void	draw_minimap(t_vars *vars);
void	draw_player(t_vars *vars);

int		keyrelease(int keycode, t_vars *vars);
int		keypress(int keycode, t_vars *vars);
void	move_up(t_vars *vars);
void	move_down(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);
void	rotate_left(t_vars *vars);
void	rotate_right(t_vars *vars);
int		is_wall(t_vars *vars, double new_px, double new_py);
int		check_edge(t_vars *vars, int new_mapx, int new_mapy);
int		close_window(void);
void	draw(t_vars *vars);
void	draw_image_test(t_vars *vars);
void	draw_pixel(t_img *img, int x, int y, int color);
void	raycast(t_vars *vars, t_ray *ray, double ra);
double	normalize_angle(double angle);
int		get_wall_dir(t_vars *vars, t_ray *ray);
double	get_distance(t_vars *vars, t_ray_util *hv);
void	rayfacing_init(t_ray *ray, double ra);
void	ray_draw(t_vars *data);
void	draw_wall(t_vars *vars, t_ray ray, int ray_index);

#endif
