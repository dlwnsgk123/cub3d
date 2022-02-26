/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:50 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/26 18:43:41 by seungiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void)
{
	exit(0);
	return (0);
}

void	put_error(char *str)
{
	printf("Error\n");
	if (str != NULL)
		printf("%s\n", str);
	exit(0);
}
