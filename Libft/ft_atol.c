/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 05:33:49 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 07:06:28 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *nbrt)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	while ((9 <= nbrt[i] && nbrt[i] <= 13) || nbrt[i] == ' ')
		i++;
	if (nbrt[i] == '-' || nbrt[i] == '+')
	{
		if (nbrt[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nbrt[i] >= '0' && nbrt[i] <= '9')
	{
		num = num * 10 + (nbrt[i] - '0');
		i++;
	}
	return (num * sign);
}
