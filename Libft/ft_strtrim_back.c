/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrin_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:17:19 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/21 00:20:20 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_back(char *s1, char *set)
{
	char	*str;
	int		end;
	int		i;

	i = 0;
	end = ft_strlen(s1);
	while (end > 0 && s1[end - 1] && ft_strchr(set, s1[end - 1]))
		end--;
	str = (char *)malloc(end + 1);
	if (str == NULL)
		return (NULL);
	while (end--)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
