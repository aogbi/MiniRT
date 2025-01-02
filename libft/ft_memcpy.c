/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 06:05:54 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/28 12:53:08 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const t_byte	*p_src;
	t_byte			*p_dst;
	const uintptr_t	*wp_src;
	uintptr_t		*wp_dst;

	if (dst == src)
		return (dst);
	wp_src = src;
	wp_dst = dst;
	if (!((uintptr_t)wp_src % alignof(uintptr_t))
		&& !((uintptr_t)wp_dst % alignof(uintptr_t)))
	{
		while (n >= sizeof(uintptr_t))
		{
			*wp_dst++ = *wp_src++;
			n -= sizeof(uintptr_t);
		}
	}
	p_src = (const t_byte *)wp_src;
	p_dst = (t_byte *)wp_dst;
	while (n--)
		*p_dst++ = *p_src++;
	return (dst);
}
