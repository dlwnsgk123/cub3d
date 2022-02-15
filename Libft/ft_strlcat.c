/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:50:42 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/16 05:32:39 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		dest_len;
	size_t		src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	j = 0;
	if (size < dest_len)
		return (size + src_len);
	while (src[j] && (j + dest_len + 1) < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (src_len + dest_len);
}
