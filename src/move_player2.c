/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:55:30 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/24 09:21:40 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
		vars->key.w = 1;
	else if (keycode == KEY_S)
		vars->key.s = 1;
	else if (keycode == KEY_A)
		vars->key.a = 1;
	else if (keycode == KEY_D)
		vars->key.d = 1;
	else if (keycode == KEY_LEFT)
		vars->key.l = 1;
	else if (keycode == KEY_RIGHT)
		vars->key.r = 1;
	return (0);
}

int	keyrelease(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->key.w = 0;
	else if (keycode == KEY_S)
		vars->key.s = 0;
	else if (keycode == KEY_A)
		vars->key.a = 0;
	else if (keycode == KEY_D)
		vars->key.d = 0;
	else if (keycode == KEY_LEFT)
		vars->key.l = 0;
	else if (keycode == KEY_RIGHT)
		vars->key.r = 0;
	return (0);
}

void	rotate_left(t_vars *vars)
{
	vars->player.pa -= PI / 100;
	if (vars->player.pa < 0)
		vars->player.pa += 2 * PI;
	vars->player.pdx = cos(vars->player.pa) * (vars->tile_size / 2);
	vars->player.pdy = sin(vars->player.pa) * (vars->tile_size / 2);
}

void	rotate_right(t_vars *vars)
{
	vars->player.pa += PI / 100;
	if (vars->player.pa > 2 * PI)
		vars->player.pa -= 2 * PI;
	vars->player.pdx = cos(vars->player.pa) * (vars->tile_size / 2);
	vars->player.pdy = sin(vars->player.pa) * (vars->tile_size / 2);
}

void	move_right(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->player.px - sin(vars->player.pa) * vars->tile_size * 0.03;
	new_y = vars->player.py + cos(vars->player.pa) * vars->tile_size * 0.03;
	if (!is_wall(vars, new_x, new_y))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}
