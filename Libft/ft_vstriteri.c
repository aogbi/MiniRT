/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vstriteri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:23:05 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 15:22:58 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vstriteri(char *str, int (*apply)(size_t *, char **, va_list *,
	void *), void *yld, ...)
{
	va_list	vargs;
	size_t	i;
	int		ctrl;

	i = 0;
	while (*str)
	{
		va_start(vargs, yld);
		ctrl = apply(&i, &str, &vargs, yld);
		va_end(vargs);
		if (ctrl == FLOW_CONTINUE)
			continue ;
		else if (!ctrl)
			break ;
		++i;
		++str;
	}
}
