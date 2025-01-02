/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackclear_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:27:05 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/01 18:26:59 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stackclear(t_stack *stack, void (*del)(void*))
{
	void	*data;

	while (ft_stackpop(&data, stack))
		if (del)
			del(data);
	free(stack->cntnr);
	free(stack);
}
