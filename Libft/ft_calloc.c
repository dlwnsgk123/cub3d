/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:56:35 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 06:51:17 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*tmp;

	tmp = malloc(n * size);
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, n * size);
	return (tmp);
}
