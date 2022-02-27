/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 03:10:05 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/27 20:11:53 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	tmp_isnum(char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (!ft_isdigit(tmp[i][j]))
				put_error("color error");
			j++;
		}
		i++;
	}
}

int	tmp_len(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

void	parse_init(t_vars *vars)
{
	vars->texture[0].ptr = NULL;
	vars->texture[1].ptr = NULL;
	vars->texture[2].ptr = NULL;
	vars->texture[3].ptr = NULL;
	vars->c_color = -1;
	vars->f_color = -1;
}

void	check_info(t_vars *vars)
{
	if (vars->c_color == -1 || vars->f_color == -1 )
		put_error("parse error : no info");
	if (vars->texture[0].ptr == NULL
		|| vars->texture[1].ptr == NULL
		|| vars->texture[2].ptr == NULL
		|| vars->texture[3].ptr == NULL)
		put_error("parse error : no info");
}
