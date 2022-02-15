/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:20 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/15 15:53:42 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	return (*(unsigned int *)
		(img->data + (x * img->bpp / 8 + y * img->size_line)));
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char			*pixel;

	pixel = img->data + (x * img->bpp / 8 + y * img->size_line);
	*(unsigned int *)pixel = color;
}

void	draw_square(t_vars *vars, int x, int y, int width, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			draw_pixel(&vars->minimap, i + x, j + y, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_vars *vars, int startX, int startY, int finishX, int finishY)
{
	int x = startX;
	int y = startY;
	int Xfactor = finishX < startX ? -1 : 1;
	int Yfactor = finishY < startY ? -1 : 1;

	int w = abs(finishX - startX);
	int h = abs(finishY - startY);
	int f;
	
	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
				f += 2 * h;
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			draw_pixel(&vars->minimap, x, y, 0x00FF00);
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
				f += 2 * w;
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			draw_pixel(&vars->minimap, x, y, 0x00FF00);
		}
	}
}

void	draw_ray(t_vars *vars, int x1, int y1, int x2, int y2)
{

}

void	draw_player(t_vars *vars)
{
	draw_square(vars,
				(int)vars->player.px, 
				(int)vars->player.py, 
				1, 0xFFFFFF);
	draw_line(vars, 
				vars->player.px,
				vars->player.py,
				vars->player.px + vars->player.pdx,
				vars->player.py + vars->player.pdy);
}

void	draw_minimap(t_vars *vars, int width, int height)
{
	int		x;
	int		y;

	y = 0;
	while (vars->map.mapdata[y] != NULL)
	{
		x = 0;
		while (vars->map.mapdata[y][x])
		{
			if (vars->map.mapdata[y][x] == '1')
				draw_square(vars, x * vars->tile_size, y * vars->tile_size, vars->tile_size, 0xbfbfbf);
			else
				draw_square(vars, x * vars->tile_size, y * vars->tile_size, vars->tile_size, 0x000000);
			x++;
		}
		y++;
	}
}
