/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:13:11 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/13 23:53:49 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	str = (char *)malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	while (j < s2_len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
