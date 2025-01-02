/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:24:05 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/27 10:38:44 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int val, size_t n)
{
	t_byte			*p_mem;
	uintptr_t		*wp_mem;
	uintptr_t		wval;
	unsigned int	i;

	wp_mem = mem;
	wval = 0;
	i = -1;
	while (++i < sizeof(uintptr_t))
		wval = (wval << CHAR_BIT) | (t_byte)val;
	if (!(uintptr_t)wp_mem % alignof(uintptr_t))
	{
		while (n >= sizeof(uintptr_t))
		{
			*wp_mem++ = wval;
			n -= sizeof(uintptr_t);
		}
	}
	p_mem = (t_byte *)wp_mem;
	while (n--)
		*p_mem++ = (t_byte)val;
	return (mem);
}
