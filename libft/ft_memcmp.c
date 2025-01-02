/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:48:57 by yhadhadi          #+#    #+#             */
/*   Updated: 2023/12/13 21:54:37 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_byte	*p_s1;
	const t_byte	*p_s2;

	p_s1 = s1;
	p_s2 = s2;
	if (p_s1 == p_s2)
		return (0);
	while (n && *p_s1 == *p_s2)
	{
		++p_s1;
		++p_s2;
		--n;
	}
	if (!n)
		return (0);
	return (*p_s1 - *p_s2);
}
