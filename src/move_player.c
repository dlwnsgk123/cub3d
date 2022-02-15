/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:37:57 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/15 06:11:12 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_wall(t_vars *vars, float x, float y)
{
    int width;
    int height;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return (1);
    width = floor(x / vars->tile_size);
    height = floor(y / vars->tile_size);
    return (vars->map.mapdata[height][width] == '1');
}

void	move_up(t_vars *vars)
{
    float new_x;
    float new_y;

    new_x = vars->player.px + cos(vars->player.pa) * vars->tile_size * 0.01;
    new_y = vars->player.py + sin(vars->player.pa) * vars->tile_size * 0.01;
    if (!is_wall(vars, new_x, new_y))
    {
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_down(t_vars *vars)
{
    float new_x;
    float new_y;

    new_x = vars->player.px - cos(vars->player.pa) * vars->tile_size * 0.01;
    new_y = vars->player.py - sin(vars->player.pa) * vars->tile_size * 0.01;
    if (!is_wall(vars, new_x, new_y))
    {
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_left(t_vars *vars)
{
    float new_x;
    float new_y;

    new_x = vars->player.px + sin(vars->player.pa) * vars->tile_size * 0.01;
    new_y = vars->player.py - cos(vars->player.pa) * vars->tile_size * 0.01;
    if (!is_wall(vars, new_x, new_y))
    {
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void	move_right(t_vars *vars)
{
    float new_x;
    float new_y;

    new_x = vars->player.px - sin(vars->player.pa) * vars->tile_size * 0.01;
    new_y = vars->player.py + cos(vars->player.pa) * vars->tile_size * 0.01;
    if (!is_wall(vars, new_x , new_y))
    {
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}

void    rotate_left(t_vars *vars)
{
    vars->player.pa -= 0.01;
    if (vars->player.pa < 0)
        vars->player.pa += 2 * PI;
    vars->player.pdx = cos(vars->player.pa) * (vars->tile_size / 2);
    vars->player.pdy = sin(vars->player.pa) * (vars->tile_size / 2);
}

void    rotate_right(t_vars *vars)
{
    vars->player.pa += 0.01;
    if (vars->player.pa > 2 * PI)
        vars->player.pa += 2 * PI;
    vars->player.pdx = cos(vars->player.pa) * (vars->tile_size / 2);
    vars->player.pdy = sin(vars->player.pa) * (vars->tile_size / 2);
}