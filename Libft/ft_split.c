/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:35:02 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 17:23:19 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*fill_str(char *str, char const *s, int str_len, int s_num)
{
	int		i;

	i = 0;
	while (str_len > 0)
	{
		if (s[s_num - str_len] == -10)
			str[i] = ' ';
		else
			str[i] = s[s_num - str_len];
		i++;
		str_len--;
	}
	str[i] = '\0';
	return (str);
}

static char	**arr_free(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	return (NULL);
}

static char	**my_split(char **strs, char const *s, char c, int words)
{
	int		i;
	int		s_num;
	int		str_len;

	i = 0;
	s_num = 0;
	str_len = 0;
	while (s[s_num] && i < words)
	{
		while (s[s_num] != '\0' && s[s_num] == c)
			s_num++;
		while (s[s_num] != '\0' && s[s_num] != c)
		{
			s_num++;
			str_len++;
		}
		strs[i] = (char *)malloc(sizeof(char) * str_len + 1);
		if (strs[i] == NULL)
			return (arr_free(strs, i));
		strs[i] = fill_str(strs[i], s, str_len, s_num);
		str_len = 0;
		i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_word(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	strs = my_split(strs, s, c, words);
	if (strs == NULL)
	{
		free(strs);
		return (NULL);
	}
	else
		strs[words] = NULL;
	return (strs);
}
