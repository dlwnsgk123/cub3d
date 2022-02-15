/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:20:20 by junhalee          #+#    #+#             */
/*   Updated: 2020/12/29 23:15:14 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int value, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = src;
	i = 0;
	while (i < size)
	{
		tmp[i] = value;
		i++;
	}
	return (src);
}
