/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:20:05 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/26 04:12:30 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (void *)s;
	i = 0;
	while (i < n)
	{
		if (tmp[i] == (unsigned char)c)
			return ((void *)tmp + i);
		i++;
	}
	return (NULL);
}
