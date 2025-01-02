/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:02:33 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/09 21:44:14 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_base_dgt(unsigned long nbr, int rdx);

char	*ft_ultoa_base(unsigned long nbr, char *base)
{
	int		rdx;
	int		off;
	char	*str;

	rdx = ft_radix(base);
	if (rdx == -1)
		return (NULL);
	off = count_base_dgt(nbr, rdx);
	str = (char *)malloc((off + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[off] = '\0';
	while (off--)
	{
		str[off] = base[nbr % rdx];
		nbr /= rdx;
	}
	return (str);
}

static int	count_base_dgt(unsigned long nbr, int rdx)
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
