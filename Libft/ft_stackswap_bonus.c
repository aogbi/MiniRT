/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackswap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:23:17 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/08 00:00:53 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackswap(t_stack *stack)
{
	size_t	penult;
	void	*buf;

	if (stack->siz == 0)
		return (0);
	if (stack->siz == 1)
		return (1);
	penult = (stack->top - 1 + stack->cap) % stack->cap;
	buf = stack->cntnr[penult];
	stack->cntnr[penult] = stack->cntnr[stack->top];
	stack->cntnr[stack->top] = buf;
	return (1);
}
