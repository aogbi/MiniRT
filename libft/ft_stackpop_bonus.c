/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:27:11 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/28 04:20:17 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackpop(void **data, t_stack *stack)
{
	if (stack->siz == 0)
		return (*data = NULL, 0);
	*data = stack->cntnr[stack->top];
	stack->cntnr[stack->top] = NULL;
	stack->top = (stack->top - 1 + stack->cap) % stack->cap;
	--stack->siz;
	return (1);
}
