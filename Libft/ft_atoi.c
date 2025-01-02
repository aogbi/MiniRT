/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:09:21 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/17 03:15:28 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
			return (LONG_MAX * (sgn > 0));
		nbr = nbr * 10 + dgt;
	}
	return (nbr * sgn);
}
