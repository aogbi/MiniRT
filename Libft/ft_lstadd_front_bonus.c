/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:43:08 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/11 21:50:06 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *node)
{
	node->next = *lst;
	if (*lst)
	{
		(*lst)->prev = node;
		while ((*lst)->prev)
			*lst = (*lst)->prev;
	}
	else
		*lst = node;
}
