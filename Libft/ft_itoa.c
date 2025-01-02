/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:06:53 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/08 21:25:44 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dgt(int nbr);

char	*ft_itoa(int nbr)
{
	int		sgn;
	int		off;
	char	*str;

	sgn = 1 | -(nbr < 0);
	off = (sgn < 0) + (count_dgt(nbr));
	str = (char *)malloc((off + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[off] = '\0';
	while (off--)
	{
		str[off] = (nbr % 10 * sgn) + 48;
		nbr /= 10;
	}
	if (sgn < 0)
		*str = '-';
	return (str);
}

static int	count_dgt(int nbr)
{
	int	cnt;

	nbr /= 10;
	cnt = 1;
	while (nbr)
	{
		nbr /= 10;
		++cnt;
	}
	return (cnt);
}
