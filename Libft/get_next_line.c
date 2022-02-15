/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:33:44 by junhalee          #+#    #+#             */
/*   Updated: 2021/10/04 20:24:59 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*str;

	i = 0;
	j = 0;
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	str = (char *)malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	free((char *)s1);
	return (str);
}

char	*get_line(char *save)
{
	char	*tmp;
	char	*rtn;
	int		n;

	tmp = ft_strchr(save, '\n');
	if (tmp != NULL)
	{
		n = tmp - save;
		rtn = ft_strndup(save, n);
	}
	else
		rtn = ft_strdup(save);
	return (rtn);
}

char	*get_save(char *save)
{
	char	*tmp;
	char	*rtn;

	tmp = ft_strchr(save, '\n');
	if (tmp == NULL)
	{
		free(save);
		return (NULL);
	}
	tmp++;
	rtn = ft_strdup(tmp);
	free(save);
	return (rtn);
}

int	ft_return(int rs)
{
	if (rs == 0)
		return (0);
	else
		return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buf;
	int			rs;

	if (fd > 10240 || fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	rs = 1;
	while (!(ft_strchr(save, '\n')) && rs != 0)
	{
		rs = read(fd, buf, BUFFER_SIZE);
		if (rs == -1)
		{
			free(buf);
			return (-1);
		}
		buf[rs] = '\0';
		save = gnl_strjoin(save, buf);
	}
	free(buf);
	*line = get_line(save);
	save = get_save(save);
	return (ft_return(rs));
}
