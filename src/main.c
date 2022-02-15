/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:16:00 by junhalee          #+#    #+#             */
/*   Updated: 2021/10/06 13:16:00 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void)
{
	exit(0);
	return (0);
}

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

void	draw(t_vars *vars)
{
	int tile_size;

	draw_minimap(vars, WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
	draw_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->minimap.ptr, 0, 0);
}

int	main_loop(t_vars *vars)
{
	if (vars->key.w == 1)
		move_up(vars);
	if (vars->key.a == 1)
		move_left(vars);
	if (vars->key.s == 1)
		move_down(vars);
	if (vars->key.d == 1)
		move_right(vars);
	if (vars->key.l == 1)
		rotate_left(vars);
	if (vars->key.r == 1)
		rotate_right(vars);
	draw(vars);
	return (0);
}

void	init_player(t_vars *vars)
{
	vars->player.pdx = cos(vars->player.pa) * vars->tile_size / 2;
    vars->player.pdy = sin(vars->player.pa) * vars->tile_size / 2;
	vars->key.w = 0;
	vars->key.a = 0;
	vars->key.s = 0;
	vars->key.d = 0;
	vars->key.r = 0;
	vars->key.l = 0;
}

int	main(int argc, char **argv)
{
	t_vars vars;
	t_img img;
	int width;
	int height;

	if (argc != 2)
		put_error("How to use : ./cub3d *.ber");
	vars.mlx = mlx_init();

	parse(argv[1], &vars);
	init_player(&vars);

	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	vars.minimap.ptr = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars.minimap.data = mlx_get_data_addr(vars.minimap.ptr, &vars.minimap.bpp, &vars.minimap.size_line, &vars.minimap.endian);
	draw(&vars);
	mlx_hook(vars.win, 2, 1L << 0, keypress, &vars);
	mlx_hook(vars.win, 3, 1L << 1, keyrelease, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop_hook(vars.mlx, &main_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
