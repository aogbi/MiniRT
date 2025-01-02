/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:48:44 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/07/29 18:33:03 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(void *m1, void *m2, size_t n);

int	ft_memswap(void *m1, void *m2, size_t n)
{
	t_byte	*aux;

	if (m1 == m2)
		return (0);
	if (n == sizeof(uint64_t) || n == sizeof(uint32_t) || n == sizeof(uint16_t))
		return (ft_swap(m1, m2, n), 1);
	if (n <= sizeof(uintptr_t))
	{
		aux = &(t_byte){0};
		while (n--)
		{
			*aux = *(t_byte *)m1;
			*(t_byte *)m1++ = *(t_byte *)m2;
			*(t_byte *)m2++ = *aux;
		}
		return (1);
	}
	aux = (t_byte *)ft_calloc(n, sizeof(t_byte));
	if (!aux)
		return (0);
	ft_memcpy(aux, m1, n);
	ft_memcpy(m1, m2, n);
	ft_memcpy(m2, aux, n);
	free(aux);
	return (1);
}

static void	ft_swap(void *m1, void *m2, size_t n)
{
	uintptr_t	*aux;

	if (n == sizeof(uint64_t))
	{
		aux = (uintptr_t *)&(uint64_t){0};
		*(uint64_t *)aux = *(uint64_t *)m1;
		*(uint64_t *)m1 = *(uint64_t *)m2;
		*(uint64_t *)m2 = *(uint64_t *)aux;
	}
	else if (n == sizeof(uint32_t))
	{
		aux = (uintptr_t *)&(uint32_t){0};
		*(uint32_t *)aux = *(uint32_t *)m1;
		*(uint32_t *)m1 = *(uint32_t *)m2;
		*(uint32_t *)m2 = *(uint32_t *)aux;
	}
	else if (n == sizeof(uint16_t))
	{
		aux = (uintptr_t *)&(uint16_t){0};
		*(uint16_t *)aux = *(uint16_t *)m1;
		*(uint16_t *)m1 = *(uint16_t *)m2;
		*(uint16_t *)m2 = *(uint16_t *)aux;
	}
}
