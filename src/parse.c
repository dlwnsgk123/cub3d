/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/27 01:35:29 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img(t_img *img, t_vars *vars, char *path)
{
	img->ptr = mlx_xpm_file_to_image(vars->mlx, path, \
							&img->width, &img->height);
	if (img->ptr == NULL)
		put_error("img path error");
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp, \
							&img->size_line, &img->endian);
	img->size_line = img->size_line / 4;
}

int	set_color(char *color_info)
{
	int		color;
	char	**tmp;
	int		r;
	int		g;
	int		b;

	tmp = ft_split(color_info, ',');
	if (tmp_len(tmp) != 3)
		put_error("color error1");
	tmp_isnum(tmp);
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		put_error("color error2");
	color = (r << 16) + (g << 8) + b;
	split_free(tmp);
	return (color);
}

void	get_info(char *line, t_vars *vars)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (ft_strcmp(tmp[0], "NO") == 0)
		set_img(&vars->texture[NO], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "SO") == 0)
		set_img(&vars->texture[SO], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "EA") == 0)
		set_img(&vars->texture[EA], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "WE") == 0)
		set_img(&vars->texture[WE], vars, tmp[1]);
	else if (ft_strcmp(tmp[0], "F") == 0)
		vars->f_color = set_color(tmp[1]);
	else if (ft_strcmp(tmp[0], "C") == 0)
		vars->c_color = set_color(tmp[1]);
	else
		put_error("mapdata error");
	split_free(tmp);
}

int	set_info(char *filename, t_vars *vars)
{
	int		fd;
	int		skip_line;
	char	*line;
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

void	parse(char *filename, t_vars *vars)
{
	int	skip_line;

	check_extension(filename);
	skip_line = set_info(filename, vars);
	check_multi_map(skip_line, filename);
	set_map_x_y(skip_line, filename, vars);
	malloc_mapdata(vars);
	set_map(skip_line, filename, vars);
	parse_map(vars);
	map_wall_check(vars);
}
