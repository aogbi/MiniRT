/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackrot_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:17:48 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/09 20:55:41 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackrot(t_stack *stack)
{
	if (stack->siz == 0)
		return (0);
	if (stack->siz == 1)
		return (1);
	stack->bot = (stack->bot - 1 + stack->cap) % stack->cap;
	if (stack->siz < stack->cap)
	{
		stack->cntnr[stack->bot] = stack->cntnr[stack->top];
		stack->cntnr[stack->top] = NULL;
	}
	stack->top = (stack->top - 1 + stack->cap) % stack->cap;
	return (1);
}
