/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:31:20 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/22 02:55:41 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	const char	*p_src = src;

	while (siz > 1 && *p_src)
	{
		*dst++ = *p_src++;
		--siz;
	}
	while (*p_src)
		++p_src;
	if (siz)
		*dst = '\0';
	return (p_src - src);
}
