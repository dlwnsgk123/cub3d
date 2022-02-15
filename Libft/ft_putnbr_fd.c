/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 23:41:17 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 07:02:18 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nb(int n, int fd)
{
	int		i;
	char	nb[10];

	i = 0;
	while (n != 0)
	{
		nb[i] = ((n % 10) + 48);
		n = n / 10;
		i++;
	}
	i = i - 1;
	while (i >= 0)
	{
		ft_putchar_fd(nb[i], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
		print_nb(n, fd);
	}
	else
		print_nb(n, fd);
}
