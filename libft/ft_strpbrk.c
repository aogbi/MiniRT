/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhadhadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:10:38 by yhadhadi          #+#    #+#             */
/*   Updated: 2024/08/21 22:10:53 by yhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *str, const char *accept)
{
	const char	*p_str = str;

	while (*p_str && !ft_strchr(accept, *p_str))
		++p_str;
	if (!*p_str)
		return (NULL);
	return ((char *)p_str);
}
