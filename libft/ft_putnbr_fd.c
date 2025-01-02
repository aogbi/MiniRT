/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:01:22 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/01/20 14:36:50 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define STR_SIZ 12

int	ft_putnbr_fd(int nbr, int fd)
{
	int		off;
	int		sgn;
	char	str[STR_SIZ];

	if (fd < 0)
		return (-1);
	off = STR_SIZ - 1;
	sgn = (nbr > 0) - (nbr < 0);
	str[off] = '\0';
	while (off--)
	{
		str[off] = ((nbr % 10) * sgn) + 48;
		if (!nbr)
			break ;
		nbr /= 10;
	}
	if (sgn < 0)
		str[off] = '-';
	off = off + (sgn > 0);
	return (write(fd, str + off, (STR_SIZ - 1) - off));
}
