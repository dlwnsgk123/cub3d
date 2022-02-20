/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:07:31 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/21 00:45:28 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_horizon_wall(t_vars *vars, char *line)
{
	int	i;
	int	len;

	i = 0;
	if (ft_strchr("NESW0", line[i]))
		put_error("wall error1");
	if (line[i] == ' ')
	{
		while (i < vars->map.x - 1 && line[i] == ' ')
			i++;
		if (ft_strchr("NESW0", line[i]))
			put_error("wall error2");
	}
	while (i < vars->map.x - 1)
	{
		if ((ft_strchr("NESW0", line[i]) && line[i + 1] == ' ')
			|| (line[i] == ' ' && ft_strchr("NESW0", line[i + 1])))
			put_error("wall error3");
		i++;
	}
}

void	check_vertical_wall(t_vars *vars, char **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < vars->map.x)
	{
		y = 0;
		if (ft_strchr("NESW0", map[y][x]))
			put_error("wall error4");
		if (map[y][x] == ' ')
		{
			while (y < vars->map.y - 1 && map[y][x] == ' ')
				y++;
			if (ft_strchr("NESW0", map[y][x]))
				put_error("wall error5");
		}
		while (y < vars->map.y - 1)
		{
			if ((ft_strchr("NESW0", map[y][x]) && map[y + 1][x] == ' ')
				|| (map[y][x] == ' ' && ft_strchr("NESW0", map[y + 1][x])))
				put_error("wall error6");
			y++;
		}
		x++;
	}
}

void	map_wall_check(t_vars *vars)
{
	char	**map;
	int		x;
	int		y;

	map = vars->map.mapdata;
	y = 0;
	check_vertical_wall(vars, map);
	while (map[y])
	{
		check_horizon_wall(vars, map[y]);
		y++;
	}
}

void	check_mapx(char *line, t_vars *vars)
{
	char	*tmp;
	int		len;

	tmp = ft_strtrim_back(line, " ");
	len = ft_strlen(tmp);
	if (len > vars->map.x)
		vars->map.x = len;
	free(tmp);
}

void	get_map_x_y(int skip_line, char *filename, t_vars *vars)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	vars->map.y = 0;
	vars->map.x = 0;
	if (fd < 0)
		put_error("map open error");
	while (skip_line--)
	{
		get_next_line(fd, &line);
		free(line);
	}
	while (get_next_line(fd, &line))
	{
		if (*line != '\0')
		{
			vars->map.y++;
			check_mapx(line, vars);
		}
		free(line);
	}
	free(line);
	close(fd);
}
