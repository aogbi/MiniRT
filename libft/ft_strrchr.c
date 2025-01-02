/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:59:12 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/22 02:56:42 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	const char	*p_str = str;

	while (*p_str)
		++p_str;
	while (p_str >= str)
	{
		if (((unsigned char)*p_str == (unsigned char)chr))
			return ((char *)p_str);
		--p_str;
	}
	return (NULL);
}
