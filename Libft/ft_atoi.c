/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:55:56 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/26 03:42:21 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nbrt)
{
	int		num;
	int		sign;
	int		i;

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
