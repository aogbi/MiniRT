/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:18:39 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/21 22:24:49 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < (len / 2))
		ft_memswap(&str[i], &str[len - 1 - i], sizeof(char));
	return (str);
}
