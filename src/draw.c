/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:20 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/23 01:28:48 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	img->data[x + y * img->size_line] = color;
}

void	draw_square(t_vars *vars, t_p p, t_p p2, int color)
{
	int		i;
	int 	j;
	int 	width;
	int 	height;

	i = 0;
	width = p2.x - p.x;
	height = p2.y - p.y;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			draw_pixel(&vars->screen, i + p.x, j + p.y, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_vars *vars, t_p start, t_p end)
{
	int x = start.x;
	int y = start.y;
	int Xfactor = end.x < start.x ? -1 : 1;
	int Yfactor = end.y < start.y ? -1 : 1;

	int w = fabs(end.x - start.x);
	int h = fabs(end.y - start.y);
	int f;
	
	if (w > h)
	{
		f = (2 * h) - w;
		for (x = start.x; x != end.x; x += Xfactor)
		{
			if (f < 0)
				f += 2 * h;
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			vars->screen.data[x + y * vars->screen.size_line] = 0x0000FF;
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = start.y; y != end.y; y += Yfactor)
		{
			if (f < 0)
				f += 2 * w;
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			vars->screen.data[x + y * vars->screen.size_line] = 0x0000FF;
		}
	}
}

void	draw_player(t_vars *vars)
{
	t_p start;
	t_p end;

	start.x = vars->player.px;
	start.y = vars->player.py;
	end.x = vars->player.px + vars->player.pdx;
	end.y = vars->player.py + vars->player.pdy;
	draw_line(vars, start, end);
}

void	draw_minimap(t_vars *vars)
{
	int		x;
	int		y;
	t_p		p;
	t_p		p2;

	y = 0;
	while (vars->map.mapdata[y])
	{
		x = 0;
		while (vars->map.mapdata[y][x])
		{
			p.x = x * vars->tile_size;
			p.y = y * vars->tile_size;
			p2.x = p.x + vars->tile_size;
			p2.y = p.y + vars->tile_size;
			if (vars->map.mapdata[y][x] == '1')
				draw_square(vars, p, p2, 0xbfbfbf);
			else
				draw_square(vars, p, p2, 0x000000);
			x++;
		}
		y++;
	}
}
