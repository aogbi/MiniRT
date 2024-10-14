/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbeforlast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:38:45 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/11 05:55:46 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstbeforlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next -> next)
		lst = lst -> next;
	return (lst);
}
