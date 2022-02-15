/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:50:47 by junhalee          #+#    #+#             */
/*   Updated: 2021/02/07 20:25:48 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->next = NULL;
}
