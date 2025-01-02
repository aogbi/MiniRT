/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:41:34 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/09 21:57:14 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_radix(char *base)
{
	int				rdx;
	int				i;
	int				chrset[128];
	unsigned char	chr;

	rdx = ft_strlen(base);
	if (rdx < 2)
		return (-1);
	i = 0;
	while (i < 128)
		chrset[i++] = 0;
	i = 0;
	while (i < rdx)
	{
		chr = base[i];
		if (chr == '-' || chr == '+')
			return (-1);
		if (chrset[chr])
			return (-1);
		chrset[chr] = 1;
		++i;
	}
	return (rdx);
}
