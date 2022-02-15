/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:08:54 by junhalee          #+#    #+#             */
/*   Updated: 2021/07/28 09:47:05 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			s_len;
	char			*s_out;

	if (s == NULL)
		return (NULL);
	s_out = (char *)malloc(sizeof(char) * len + 1);
	if (s_out == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len > start + len)
		s_len = start + len;
	i = start;
	while (i < s_len)
	{
		s_out[i - start] = s[i];
		i++;
	}
	s_out[i - start] = 0;
	return (s_out);
}
