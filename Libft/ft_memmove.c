/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:50:32 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/26 14:47:09 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*dest_tmp;
	const unsigned char		*src_tmp;
	int						i;

	dest_tmp = dest;
	src_tmp = src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest <= src)
	{
		while (n--)
		{
			dest_tmp[i] = src_tmp[i];
			i++;
		}
	}
	else
	{
		while (n--)
		{
			dest_tmp[n] = src_tmp[n];
		}
	}
	return (dest);
}
