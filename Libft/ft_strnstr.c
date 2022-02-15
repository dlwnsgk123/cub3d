/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:20:57 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 09:45:09 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	find_len;
	size_t	i;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	find_len = ft_strlen(to_find);
	while (str[i] != '\0' && len >= find_len)
	{
		if (str[i] == *to_find && ft_strncmp(str + i, to_find, find_len) == 0)
			return ((char *)str + i);
		i++;
		len--;
	}
	return (NULL);
}
