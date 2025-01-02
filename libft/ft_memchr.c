/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 03:17:50 by yhadhadi          #+#    #+#             */
/*   Updated: 2023/12/18 16:10:41 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int val, size_t n)
{
	const t_byte	*p_mem;

	p_mem = mem;
	while (n--)
	{
		if (*p_mem == (t_byte)val)
			return ((void *)p_mem);
		++p_mem;
	}
	return (NULL);
}
