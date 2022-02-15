/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:19:59 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/26 00:46:20 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;
	int					i;

	i = 0;
	dest_tmp = dest;
	src_tmp = src;
	while (n > 0)
	{
		if (src_tmp[i] != (unsigned char)c)
		{
			dest_tmp[i] = src_tmp[i];
			i++;
		}
		else
		{
			dest_tmp[i] = src_tmp[i];
			i++;
			return (dest_tmp + i);
		}
		n--;
	}
	return (NULL);
}
