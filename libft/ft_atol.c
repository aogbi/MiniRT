/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:53:36 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/17 03:15:18 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		sgn;
	int		dgt;
	long	nbr;

	while (ft_isspace(*str))
		++str;
	sgn = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sgn *= -1;
	}
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		dgt = *str++ - 48;
		if (nbr > (LONG_MAX - dgt) / 10)
			return (LONG_MAX * (sgn > 0) + LONG_MIN * (sgn < 0));
		nbr = nbr * 10 + dgt;
	}
	return (nbr * sgn);
}
