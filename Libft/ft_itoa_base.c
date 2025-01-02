/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:06 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/09 21:57:40 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_base_dgt(long nbr, int rdx);

char	*ft_itoa_base(int nbr, char *base)
{
	int		rdx;
	int		sgn;
	int		off;
	long	val;
	char	*str;

	rdx = ft_radix(base);
	if (rdx == -1)
		return (NULL);
	sgn = 1 | -(rdx == 10 && nbr < 0);
	val = (rdx == 10) * (long)nbr | ((rdx != 10) * (unsigned int)nbr);
	off = (rdx == 10 && sgn < 0) + (count_base_dgt(val, rdx));
	str = (char *)malloc((off + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[off] = '\0';
	while (off--)
	{
		str[off] = base[val % rdx * sgn];
		val /= rdx;
	}
	if (rdx == 10 && sgn < 0)
		*str = '-';
	return (str);
}

static int	count_base_dgt(long nbr, int rdx)
{
	int	cnt;

	nbr /= rdx;
	cnt = 1;
	while (nbr)
	{
		nbr /= rdx;
		++cnt;
	}
	return (cnt);
}
