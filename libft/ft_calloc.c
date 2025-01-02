/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 06:21:34 by yhadhadi          #+#    #+#             */
/*   Updated: 2023/12/18 18:13:17 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t siz)
{
	size_t	alloc_siz;
	void	*mem;

	if (siz && n > SIZE_MAX / siz)
		return (NULL);
	alloc_siz = n * siz;
	mem = malloc(alloc_siz);
	if (!mem)
		return (NULL);
	else
		ft_bzero(mem, alloc_siz);
	return (mem);
}
