/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:20:30 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/17 03:22:10 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*apply)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*map;
	void	*data;

	map = NULL;
	while (lst)
	{
		data = apply(lst->data);
		node = ft_lstnew(data);
		if (!node)
		{
			if (del && data)
				del(data);
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, node);
		lst = lst->next;
	}
	return (map);
}
