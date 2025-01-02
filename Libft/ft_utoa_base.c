/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:15:09 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/11 02:17:30 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_base_dgt(unsigned int nbr, int rdx);

char	*ft_utoa_base(unsigned int nbr, char *base)
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

static int	count_base_dgt(unsigned int nbr, int rdx)
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
