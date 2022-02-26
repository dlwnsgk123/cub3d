/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:52:22 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/26 19:39:01 by seungiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_edge(t_vars *vars, int new_mapx, int new_mapy)
{
	int	old_mapx;
	int	old_mapy;
	int	dx;
	int	dy;

	old_mapx = floor(vars->player.px / TILE_SIZE);
	old_mapy = floor(vars->player.py / TILE_SIZE);
	dx = new_mapx - old_mapx;
	dy = new_mapy - old_mapy;
	if (old_mapx == new_mapx || old_mapy == new_mapy)
		return (0);
	if ((dx == 1 || dx == -1) && (dy == 1 || dy == -1))
	{	
		if (vars->map.mapdata[old_mapy][old_mapx + dx] == '1'\
				&& vars->map.mapdata[old_mapy + dy][old_mapx] == '1')
			return (1);
	}
	return (0);
}

int	is_wall(t_vars *vars, double check_x, double check_y)
{
	int	new_mapx;
	int	new_mapy;

	new_mapx = (int)floor(check_x / TILE_SIZE);
	new_mapy = (int)floor(check_y / TILE_SIZE);
	if (new_mapx > vars->map.x || new_mapx < 0 \
			|| new_mapy > vars->map.y - 1 || new_mapy < 0)
		return (1);
	if (check_edge(vars, new_mapx, new_mapy))
		return (1);
	return (vars->map.mapdata[new_mapy][new_mapx] == '1');
}

void	move_up(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->player.px + (cos(vars->player.pa) * TILE_SIZE * 0.1);
	new_y = vars->player.py + (sin(vars->player.pa) * TILE_SIZE * 0.1);
	if (!is_wall(vars, \
			vars->player.px + vars->player.pdx, \
			vars->player.py + vars->player.pdy))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_down(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->player.px - cos(vars->player.pa) * TILE_SIZE * 0.1;
	new_y = vars->player.py - sin(vars->player.pa) * TILE_SIZE * 0.1;
	if (!is_wall(vars, \
			vars->player.px - vars->player.pdx, \
			vars->player.py - vars->player.pdy))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_left(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->player.px + sin(vars->player.pa) * TILE_SIZE * 0.1;
	new_y = vars->player.py - cos(vars->player.pa) * TILE_SIZE * 0.1;
	if (!is_wall(vars, \
			vars->player.px + vars->player.pdy, \
			vars->player.py - vars->player.pdx))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}
