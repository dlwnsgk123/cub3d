/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:31:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/15 06:15:34 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../Libft/libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MINIMAP_WIDTH WINDOW_WIDTH / 2
# define MINIMAP_HEIGHT WINDOW_HEIGHT / 2
# define PI		3.14159265358979323846	
# define PI_2	1.57079632679489661923
# define PI_4	0.78539816339744830962

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

typedef struct s_img
{
	void	*ptr;
	char	*data;
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
	t_key 		key;
	t_img 		screen;
	t_img 		minimap;
	t_img		texture[4];
	int 		f_color;
	int 		c_color;
	t_map		 map;
	t_player	player;
	int 		tile_size;
} 				t_vars;

void	put_error(char *str);
void	parse(char *filename, t_vars *vars);
void	set_map(int skip_line, char *filename, t_vars *vars);
void 	get_map_x_y(int skip_line, char *filename, t_vars *vars);
void 	draw_minimap(t_vars *vars, int width, int height);
void 	draw_player(t_vars *vars);
void 	img_set(t_vars *vars, t_img *img, char *path, int type);
void	img_init(t_vars *vars);
void	move_up(t_vars *vars);
void	move_down(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);
void	rotate_left(t_vars *vars);
void 	rotate_right(t_vars *vars);
void 	check_map_size(t_vars *vars);
void	draw_screen(t_vars *vars, t_img *img, int x, int y);
int		close_window(void);
void	draw(t_vars *vars);

#endif