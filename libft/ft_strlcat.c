/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:36:07 by yhadhadi          #+#    #+#             */
/*   Updated: 2023/12/11 22:42:23 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t		src_len;
	char		*p_dst;
	size_t		off;

	src_len = ft_strlen(src);
	if (!siz)
		return (src_len);
	p_dst = dst;
	while (*p_dst)
		++p_dst;
	off = p_dst - dst;
	while (siz > off + 1 && *src)
	{
		*p_dst++ = *src++;
		--siz;
	}
	if (siz <= off)
		return (siz + src_len);
	*p_dst = '\0';
	return (off + src_len);
}
