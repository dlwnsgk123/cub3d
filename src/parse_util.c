/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 03:10:05 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/21 03:12:18 by junhalee         ###   ########.fr       */
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

int	tmp_len(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}
