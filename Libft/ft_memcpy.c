/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:20:16 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/26 01:02:51 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*dest_tmp;
	const char		*src_tmp;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_tmp = dest;
	src_tmp = src;
	i = 0;
	while (i < n)
	{
		dest_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
