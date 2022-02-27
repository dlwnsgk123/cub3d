/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:07:31 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/27 09:43:36 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_row_line(t_vars *vars, char *line)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = ft_strtrim_back(line, " ");
	len = ft_strlen(tmp);
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
	while (i < len)
	{
		if ((ft_strchr("NESW0", line[i]) && \
				(line[i + 1] == ' ' || line[i + 1] == '\0')) || \
				(line[i] == ' ' && ft_strchr("NESW0", line[i + 1])))
			put_error("wall error3");
		i++;
	}
	free(tmp);
}

static void	check_col_line(t_vars *vars, char **map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < vars->map.x)
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
			if ((ft_strchr("NESW0", map[y][x]) && \
					(map[y + 1][x] == ' ' || map[y + 1] == NULL)) || \
					(map[y][x] == ' ' && ft_strchr("NESW0", map[y + 1][x])))
				put_error("wall error6");
			y++;
		}
	}
}

void	map_wall_check(t_vars *vars)
{
	char	**map;
	int		y;

	map = vars->map.mapdata;
	y = 0;
	check_col_line(vars, map);
	while (map[y])
	{
		check_row_line(vars, map[y]);
		y++;
	}
}

void	map_prev_skip(int fd, int skip_line, char *line)
{
	while (skip_line--)
	{
		get_next_line(fd, &line);
		free(line);
	}
	get_next_line(fd, &line);
	while (*line == '\0')
	{
		free(line);
		get_next_line(fd, &line);
	}
}

void	check_multi_map(int skip_line, char *filename)
{
	int		fd;
	int		map_end;
	char	*line;

	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		put_error("map open error");
	map_prev_skip(fd, skip_line, line);
	free(line);
	while (get_next_line(fd, &line))
	{
		if (map_end == 1)
			put_error("multi map error");
		if (*line == '\0')
			map_end = 1;
		free(line);
	}
	free(line);
	close(fd);
}
