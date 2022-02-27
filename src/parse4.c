/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:13:28 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/27 20:10:45 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_mapdata(t_vars *vars, char *mapdata, char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		mapdata[i] = line[i];
		i++;
	}
	while (i < vars->map.x)
	{
		mapdata[i] = ' ';
		i++;
	}
	mapdata[vars->map.x] = '\0';
	free(line);
}

void	set_map(int skip_line, char *filename, t_vars *vars)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
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
			copy_mapdata(vars, vars->map.mapdata[i], \
						ft_strtrim_back(line, " "));
			i++;
		}
		free(line);
	}
	free(line);
}

void	check_extension(char *filename)
{
	int		len;
	char	*ext;

	len = ft_strlen(filename);
	if (len < 5)
		put_error("file extension error");
	ext = &filename[len - 4];
	if (ft_strncmp(ext, ".cub", 4) != 0)
		put_error("file extension error");
}
