/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:52:22 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/23 13:44:13 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_edge(t_vars *vars, int new_mapx, int new_mapy)
{
	int	old_mapx;
	int	old_mapy;
	int	dx;
	int	dy;

	old_mapx = floor(vars->player.px / vars->tile_size);
	old_mapy = floor(vars->player.py / vars->tile_size);
	dx = new_mapx - old_mapx;
	dy = new_mapy - old_mapy;
	if (old_mapx == new_mapx || old_mapy == new_mapy)
		return (0);
	if (vars->map.mapdata[old_mapy][old_mapx + dx] == '1'\
			&& vars->map.mapdata[old_mapy + dy][old_mapx] == '1')
		return (1);
	return (0);
}

int	is_wall(t_vars *vars, float new_px, float new_py)
{
	int	new_mapx;
	int	new_mapy;

	if (new_px < 0 || new_px > WINDOW_WIDTH
		|| new_py < 0 || new_py > WINDOW_HEIGHT)
		return (1);
	new_mapx = floor(new_px / vars->tile_size);
	new_mapy = floor(new_py / vars->tile_size);
	if (check_edge(vars, new_mapx, new_mapy))
		return (1);
	return (vars->map.mapdata[new_mapy][new_mapx] == '1');
}

void	move_up(t_vars *vars)
{
	float	new_x;
	float	new_y;

	new_x = vars->player.px + cos(vars->player.pa) * vars->tile_size * 0.05;
	new_y = vars->player.py + sin(vars->player.pa) * vars->tile_size * 0.05;
	if (!is_wall(vars, new_x, new_y))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_down(t_vars *vars)
{
	float	new_x;
	float	new_y;

	new_x = vars->player.px - cos(vars->player.pa) * vars->tile_size * 0.05;
	new_y = vars->player.py - sin(vars->player.pa) * vars->tile_size * 0.05;
	if (!is_wall(vars, new_x, new_y))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_left(t_vars *vars)
{
	float	new_x;
	float	new_y;

	new_x = vars->player.px + sin(vars->player.pa) * vars->tile_size * 0.05;
	new_y = vars->player.py - cos(vars->player.pa) * vars->tile_size * 0.05;
	if (!is_wall(vars, new_x, new_y))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}
