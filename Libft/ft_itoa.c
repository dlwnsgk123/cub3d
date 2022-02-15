/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:12:07 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 07:01:08 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long long n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	get_sign(long long n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	int			len;
	long long	num;
	int			sign;
	char		*str;

	num = (long long)n;
	sign = get_sign(num);
	len = numlen(num);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (num < 0)
		num = -1 * num;
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = (num % 10) + 48;
		num = (num / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
