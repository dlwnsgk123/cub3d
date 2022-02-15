/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:20:25 by junhalee          #+#    #+#             */
/*   Updated: 2021/09/27 04:43:57 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
