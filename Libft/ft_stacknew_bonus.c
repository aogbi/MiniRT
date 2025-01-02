/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacknew_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:27:09 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/28 04:20:17 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stacknew(size_t cap)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	*stack = (t_stack){.cntnr = (void **)ft_calloc(cap, sizeof(void *)),
		.cap = cap, .top = cap - 1};
	if (!cap || !stack->cntnr)
		return (free(stack), NULL);
	return (stack);
}
