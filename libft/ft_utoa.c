/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:59:34 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/02/11 02:10:24 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dgt(unsigned int nbr);

char	*ft_utoa(unsigned int nbr)
{
	int		off;
	char	*str;

	off = count_dgt(nbr);
	str = (char *)malloc((off + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[off] = '\0';
	while (off--)
	{
		str[off] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (str);
}

static int	count_dgt(unsigned int nbr)
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
