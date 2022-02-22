/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:31:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/22 21:45:42 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../Libft/libft.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720
# define MINIMAP_WIDTH	WINDOW_WIDTH
# define MINIMAP_HEIGHT	WINDOW_HEIGHT
# define FOV_ANGLE		1.0471975512
# define PI				3.14159265358979323846	
# define PI_2			1.57079632679489661923
# define PI_4			0.78539816339744830962

typedef struct s_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
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

typedef struct s_mpl
{
	double	dy;
	double	ddy;
	double	dx;
	double	ddx;
	double	dv;
	double	incx;
	double	incy;
	double	error;
	double	errorprev;
}	t_mpl;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	t_mpl	v;
	t_point	pos;	//플레이어가 바라보는 방향
	t_point	s_dir;	//scale이 적용된 hit 위치
	t_point m_dir;	//벽에 hit한 위치
	t_point	prev_dir;
	int	hit;		//hit한 방향 4:N, 3:S, 2:E, 1:W
}	t_ray;

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
	t_map		 map;
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
int		is_wall(t_vars *vars, float new_px, float new_py);
int		check_edge(t_vars *vars, int new_mapx, int new_mapy);


int		close_window(void);
void	draw(t_vars *vars);

void	draw_image_test(t_vars *vars);
void	ray_draw(t_vars *data);
void	draw_line(t_vars *vars, t_p start, t_p end);
void	draw_pixel(t_img *img, int x, int y, int color);
#endif