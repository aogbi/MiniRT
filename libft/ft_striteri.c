/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:44:40 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/02 15:22:58 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, int (*apply)(size_t *, char **, void *),
	void *yld)
{
	size_t	i;
	int		ctrl;

	i = 0;
	while (*str)
	{
		ctrl = apply(&i, &str, yld);
		if (ctrl == FLOW_CONTINUE)
			continue ;
		else if (!ctrl)
			break ;
		++i;
		++str;
	}
}
