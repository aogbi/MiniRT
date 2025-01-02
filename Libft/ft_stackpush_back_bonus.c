/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpush_back_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:22:19 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/28 04:20:17 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackpush_back(t_stack *stack, void *data)
{
	if (stack->siz == stack->cap)
		return (0);
	stack->bot = (stack->bot - 1 + stack->cap) % stack->cap;
	stack->cntnr[stack->bot] = data;
	++stack->siz;
	return (1);
}
