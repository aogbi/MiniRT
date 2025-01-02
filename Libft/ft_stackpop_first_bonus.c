/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop_first_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:22:17 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/28 04:20:17 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stackpop_first(void **data, t_stack *stack)
{
	if (stack->siz == 0)
		return (*data = NULL, 0);
	*data = stack->cntnr[stack->bot];
	stack->cntnr[stack->bot] = NULL;
	stack->bot = (stack->bot + 1) % stack->cap;
	--stack->siz;
	return (1);
}
