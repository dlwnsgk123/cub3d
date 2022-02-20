/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/20 20:43:27 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void split_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str[i]);
    free(str);
}

void	malloc_mapdata(t_vars *vars)
{
	int i;

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

int		tmp_len(char **tmp)
{
	int i;

	i = 0;
	while(tmp[i])
		i++;
	return (i);
}

void	set_img(t_img *img, t_vars *vars, char *path)
{
	img->ptr = mlx_xpm_file_to_image(vars->mlx, path, &img->width, &img->height);
	if (img->ptr == NULL)
		put_error("img path error");
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
}

int		set_color(char *color_info)
{
	int		color;
	char	**tmp;

	tmp = ft_split(color_info, ',');
	if (tmp_len(tmp) != 3)
		put_error("color error");
	color = (ft_atoi(tmp[0]) * 256 * 256) + (ft_atoi(tmp[1]) * 256) + ft_atoi(tmp[2]);
	split_free(tmp);
	return (color);
}

void	get_info(char *line, t_vars *vars)
{
	char **tmp;
	int	width;
	int	height;

	tmp = ft_split(line, ' ');
	if (ft_strcmp(tmp[0], "EA") == 0)
		set_img(&vars->texture[0], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "WE") == 0)
		set_img(&vars->texture[1], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "SO") == 0)
		set_img(&vars->texture[2], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "NO") == 0)
		set_img(&vars->texture[3], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "F") == 0)
		vars->f_color = set_color(tmp[1]);
	else if (ft_strcmp(tmp[0], "C") == 0)
		vars->c_color = set_color(tmp[1]);
	else
		put_error("mapdata error");
	split_free(tmp);
}

int		set_info(char *filename, t_vars *vars)
{
	int		fd;
	int 	skip_line;
	char 	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		put_error("map open error");
	count = 0;
	skip_line = 0;
	while (get_next_line(fd, &line))
	{
		if (*line != '\0' && count < 6)
		{
			get_info(line, vars);
			count++;
			skip_line++;
		}
		else if (count != 6)
			skip_line++;
		free(line);
	}
	free(line);
	close(fd);
	return (skip_line);
}

char	*ft_strtrim_back(char *s1, char *set)
{
	char	*str;
	int		end;
	int		i;

	i = 0;
	end = ft_strlen(s1);
	while (end > 0 && s1[end - 1] && ft_strchr(set, s1[end - 1]))
		end--;
	str = (char *)malloc(end + 1);
	if (str == NULL)
		return (NULL);
	while (end--)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	check_mapx(char *line, t_vars *vars)
{
	char	*tmp;
	int 	len;

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

void	copy_mapdata(t_vars *vars ,char *mapdata, char *line)
{
	int i;
	int len;

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
	int 	fd;
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
			copy_mapdata(vars, vars->map.mapdata[i], ft_strtrim_back(line, " "));
			i++;
		}
		free(line);
	}
	free(line);
}

void	print_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.mapdata[i] != NULL)
	{
		printf("||%s||\n", vars->map.mapdata[i]);
		i++;
	}
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
	int 	x;
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
				if (flag > 1)
					put_error("mapdata error");
				set_player_angle(vars, mapdata[y][x]);
				vars->player.px = x * vars->tile_size + vars->tile_size / 2;
				vars->player.py = y * vars->tile_size + vars->tile_size / 2;
				flag++;
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

void	check_horizon_wall(t_vars *vars, char *line)
{
	int i;
	int len;

	i = 0;
	if (ft_strchr("NESW0", line[i]))
		put_error("wall error1");
	if (line[i] == ' ')
	{
		while(i < vars->map.x - 1 && line[i] == ' ')
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
	int x;
	int y;

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
	int 	x;
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

void	parse(char *filename, t_vars *vars)
{
	int skip_line;

	check_extension(filename);
	skip_line = set_info(filename, vars);
	get_map_x_y(skip_line, filename, vars);
	set_tile_size(vars);
	malloc_mapdata(vars);
	set_map(skip_line, filename, vars);
	parse_map(vars);
	map_wall_check(vars);
}
