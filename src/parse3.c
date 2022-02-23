/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:11:38 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/23 13:51:20 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_mapdata(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.mapdata = (char **)malloc(sizeof(char *) * (vars->map.y + 1));
	if (vars->map.mapdata == NULL)
		put_error("malloc error");
	while (i < vars->map.y)
	{
		vars->map.mapdata[i] = (char *)malloc(sizeof(char) * (vars->map.x + 1));
		if (vars->map.mapdata[i] == NULL)
			put_error("malloc error");
		i++;
	}
	vars->map.mapdata[vars->map.y] = NULL;
}

void	set_player_angle(t_vars *vars, char c)
{
	if (c == 'N')
		vars->player.pa = 4.71238898038;
	if (c == 'S')
		vars->player.pa = PI_2;
	if (c == 'E')
		vars->player.pa = 0;
	if (c == 'W')
		vars->player.pa = PI;
}

void	parse_map(t_vars *vars)
{
	char	**mapdata;
	int		x;
	int		y;
	int		flag;

	mapdata = vars->map.mapdata;
	y = -1;
	flag = 0;
	while (mapdata[++y] != NULL)
	{
		x = -1;
		while (mapdata[y][++x] != '\0')
		{
			if (!ft_strchr(" 01NSEW", mapdata[y][x]))
				put_error("map data error");
			if (ft_strchr("NESW", mapdata[y][x]))
			{
				if (flag++ > 1)
					put_error("mapdata error");
				set_player_angle(vars, mapdata[y][x]);
				vars->player.px = x * vars->tile_size + vars->tile_size / 2;
				vars->player.py = y * vars->tile_size + vars->tile_size / 2;
			}
		}
	}
}

void	set_tile_size(t_vars *vars)
{
	if (MINIMAP_WIDTH / vars->map.x < MINIMAP_HEIGHT / vars->map.y)
		vars->tile_size = MINIMAP_WIDTH / vars->map.x;
	else
		vars->tile_size = MINIMAP_HEIGHT / vars->map.y;
}
