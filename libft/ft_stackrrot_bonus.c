/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackrrot_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:17:53 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/07 23:19:44 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackrrot(t_stack *stack)
{
	if (stack->siz == 0)
		return (0);
	if (stack->siz == 1)
		return (1);
	stack->top = (stack->top + 1) % stack->cap;
	if (stack->siz < stack->cap)
	{
		stack->cntnr[stack->top] = stack->cntnr[stack->bot];
		stack->cntnr[stack->bot] = NULL;
	}
	stack->bot = (stack->bot + 1) % stack->cap;
	return (1);
}
