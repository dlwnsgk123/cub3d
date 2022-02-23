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

static void	draw_f_c(t_vars *data)
{
	int	i, j;
	int	y = data->screen.size_line;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			data->screen.data[(i * y) + j] = data->c_color;
			data->screen.data[((WINDOW_HEIGHT - i - 1) * y) + j] = data->f_color;
			j++;
		}
		i++;
	}
}

int	close_window(void)
{
	exit(0);
	return (0);
}

void	draw(t_vars *vars)
{
//	draw_player(vars);
	draw_f_c(vars);
//	draw_minimap(vars);
	ray_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->screen.ptr, 0, 0);
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
	if (vars->key.w == 1 || vars->key.a == 1 || vars->key.s == 1 || vars->key.d == 1 || vars->key.l == 1 || vars->key.r == 1)
		draw(vars);
	return (0);
}

void	init(t_vars *vars)
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
	t_vars	vars;
	t_img	img;

	if (argc != 2)
		put_error("How to use : ./cub3d *.ber");
	vars.mlx = mlx_init();
	parse(argv[1], &vars);
	init(&vars);
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	vars.screen.ptr = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars.screen.data = (int *)mlx_get_data_addr(vars.screen.ptr, &vars.screen.bpp, \
								&vars.screen.size_line, &vars.screen.endian);
	vars.screen.size_line = vars.screen.size_line / 4;
	draw(&vars);
	mlx_hook(vars.win, 2, 1L << 0, keypress, &vars);
	mlx_hook(vars.win, 3, 1L << 1, keyrelease, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop_hook(vars.mlx, main_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
