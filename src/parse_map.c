/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/15 16:53:21 by junhalee         ###   ########.fr       */
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
	vars->map.mapdata = (char **)malloc(sizeof(char *) * (vars->map.y + 1));
	if (vars->map.mapdata == NULL)
		put_error("malloc error");
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
		put_error("color info error");
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
	if (tmp_len(tmp) != 2)
		put_error("img path error");
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

void	get_map_x_y(int skip_line, char *filename, t_vars *vars)
{
	int		fd;
	int 	tmp;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		put_error("map open error");
	vars->map.y = 0;
	vars->map.x = 0;
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
			tmp = ft_strlen(line);
			if (tmp > vars->map.x)
				vars->map.x = tmp;
		}
		free(line);
	}
	free(line);
	close(fd);
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
			vars->map.mapdata[i] = ft_strdup(line);
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
		printf("%s\n", vars->map.mapdata[i]);
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
	y = 0;
	while (mapdata[y] != NULL)
	{
		x = 0;
		while (mapdata[y][x] != '\0')
		{
			if (!ft_strchr(" 01NSEW", mapdata[y][x]))
				put_error("map data error");
			if (ft_strchr("NESW", mapdata[y][x]))
			{
				if (flag == 1)
					put_error("mapdata error");
				set_player_angle(vars, mapdata[y][x]);
				vars->player.px = x * vars->tile_size + vars->tile_size / 2;
				vars->player.py = y * vars->tile_size + vars->tile_size / 2;
				flag = 1;
			}
			x++;
		}
		y++;
	}
}

void	set_tile_size(t_vars *vars)
{
	if (MINIMAP_WIDTH / vars->map.x < MINIMAP_HEIGHT / vars->map.y)
		vars->tile_size = MINIMAP_WIDTH/ vars->map.x * 2;
	else
		vars->tile_size = MINIMAP_HEIGHT / vars->map.y * 2;
}

int	check_line(char **map, char *line, int index)
{
	int i;

	i = 0;
	if (index == 0)
	{
		while (line[i])
		{
			if (line[i] == ' ' && i < ft_strlen(map[index + 1]))
				if (map[index + 1][i] != '1')
					return (1);
			i++;
		}
	}
	return (0);
}

void	map_check(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	map = vars->map.mapdata;
	j = 0;
	while (map[j])
	{
		if (check_line(map, map[j], j))
			put_error("map error");
		j++;
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
	map_check(vars);
}
