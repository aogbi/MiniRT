/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 07:05:53 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/27 10:38:43 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	t_byte			*p_dst;
	const t_byte	*p_src;

	p_dst = dst;
	p_src = src;
	if (p_dst == p_src)
		return (p_dst);
	if (p_dst <= p_src || p_dst >= p_src + n)
		ft_memcpy(dst, src, n);
	else
	{
		p_dst += n;
		p_src += n;
		while (n--)
			*--p_dst = *--p_src;
	}
	return (dst);
}
