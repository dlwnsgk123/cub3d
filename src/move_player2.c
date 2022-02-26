/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:55:30 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/26 20:53:33 by junhalee         ###   ########.fr       */
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
	vars->player.pa -= 0.2;
	if (vars->player.pa < 0)
		vars->player.pa += 2 * PI;
	vars->player.pdx = cos(vars->player.pa) * (TILE_SIZE / 4);
	vars->player.pdy = sin(vars->player.pa) * (TILE_SIZE / 4);
}

void	rotate_right(t_vars *vars)
{
	vars->player.pa += 0.2;
	if (vars->player.pa > 2 * PI)
		vars->player.pa -= 2 * PI;
	vars->player.pdx = cos(vars->player.pa) * (TILE_SIZE / 4);
	vars->player.pdy = sin(vars->player.pa) * (TILE_SIZE / 4);
}

void	move_right(t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->player.px - sin(vars->player.pa) * TILE_SIZE * 0.1;
	new_y = vars->player.py + cos(vars->player.pa) * TILE_SIZE * 0.1;
	if (!is_wall(vars, \
			vars->player.px - vars->player.pdy, \
			vars->player.py + vars->player.pdx))
	{
		vars->player.px = new_x;
		vars->player.py = new_y;
	}
}
